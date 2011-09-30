=begin
= cstruct.rb

cstruct.rb provides a ruby module which allows  access to structured 
binary data in a decent way.
The data-structures are described in a c-style manner, access is done with
ruby methods.

== Vesion
  $Id: cstruct.rb,v 1.4 2002/03/18 23:39:31 thus Exp $

== Example
  require 'cstruct'

  CStruct.defStruct "TheCType",<<-"END_TYP"
    uint16_t 	elt1;
    uint8_t 	elt2;
    uint8_t 	elt3[2];
    END_TYP

  cVar        = CStruct::TheCType.new
  cVar.elt1   = 0x4548
  cVar.elt2   = 0x4c
  cVar.elt3[0]= 0x4c
  cVar.elt3[1]= 0x4f
  puts          cVar
  puts          cVar.toBin
  File.open("test","w"){|f| cVar.write(f)}

== CStruct module
CStruct provides some methods which let you define some data structures
(CStruct.defStruct and CStruct.defBaseT).
The definitions are parsed from ascii-input strings.
The definition format is very similar to a simple C-structure definition.
The main goal of this module was to give access to some binary data files
which were written by a c-program. Your sole job should be to copy the 
structure-definitions from the c-header-files into a ruby script,
give it to CStruct.defStruct as a string and then you can read or write
the binary data.

The method CStruct.defStruct defines a ruby class in the module CStruct
with a given class name (first char should be uppercase, spaces are 
replaced by underscore).
You can instantiate such a class with CStruct::TheCType.new() and then 
access each member by the appropriate member functions.

The data-types of the structure elements can be either base types or
structure types or arrays of them.

Both base types and structure types must be defined before usage.

If the data structure contains holes caused by the alignment (default = 4)
then dummy members are generated automatically.


=== methods
--- CStruct.defBaseT(name,sizeof,signed)
    Define a base-type. the 6-posix inttypes int8_t..uint32_t are already
    predefined in the module CStruct.
    parameter sizeof can be 1,2,4
    parameter signed can be true or false

--- CStruct.defStruct
    Define a structured type with means of an ascii-string.
    Line by line.


=== methods of generated c-type-classes



--- fromBin
    convert a binary string representation into the data structure 

--- read
    like fromBin, but read binary data from a file instead of a string

--- toBin
    convert the whole data structure into a binary representation and
    return this as a string

--- write
    like toBin, but write binary data to a file

--- sizeof
    return the size of the data-structure. This method exists both as a
    class-method an an object-method

--- 'userelement'=
    this method exists for each Element of the data structure and lets
    you write the appropriate data member

--- 'userelement'
    this method exists for each Element of the data structure and lets
    you read the appropriate data member

--- to_s
    return a string representation of the whole data structure.
    This is used by puts


== Todo
  * bitfields
  * support 'strict alignMent'
  * support big and little endianess
  * float-support
  * support symbolic array-sizes
  * copy whole structures
  * generic access to the data by string keys --> workaround: use eval

== Bugs

== References
== License
You can use/re-distribute/change CStruct under Rubys License or GPL.
== Author
  Thomas Husterer 
  s-t.husterer@t-online.de

=end

module CStruct
  @@alignment=4
  def CStruct.alignment=(align) @@alignment= align                        end
  def CStruct.alignment()@@alignment                                      end
  class CStructBase
    attr_reader :offset
    def initialize(offset)   @offset=offset; @membn=[]; @membv={};           end
    def each() @membn.each{|n| yield n,@membv[n].get,@membv[n].obj} end
    def child(n)      @membv[n]; end
    def obj()            self;                                            end
    def get()            self;                                            end
    def sizeof()         self.class.sizeof                                end
    def toBin() ret= ""; @membn.each { |n|; ret += @membv[n].toBin}; ret; end
    def fromBin(b,i=0)   @membn.each { |n|; i=@membv[n].fromBin(b,i)}; i; end
    def read(f)          fromBin(f.read(sizeof()))                        end
    def write(f)         f.write(toBin)                                   end
    def to_s()           to_sInternal(0)[0]                               end
    def to_sInternal(ofs,nest=0)
      s=nest>0 ? "\n" : ""; 
      @membn.each { |n|;
        #ofs==@membv[n].offset or raise " bad offset #{ofs} != #{@membv[n].offset}"
        s+=sprintf("%3d ",@membv[n].offset)
        x,ofs = @membv[n].to_sInternal(ofs,nest+1)
        s+="    "*nest + "#{n}\t= "+x
      }; 
      [s+"\n",ofs]
    end
  end
  class BaseT < CStructBase
  end

  class CArray < CStructBase
    def initialize(offset,n,typ) 
      super(offset);  
      n.times{|j|  i=j.to_s
        @membn.push i; 
        @membv[i]  = typ.new(offset);
        offset     += @membv[i].sizeof()
      }
    end
    def []=(i,v) @membv[i.to_s].set(v)                                         end
    def [](i)    @membv[i.to_s].get()                                         end
  end
  class CString < BaseT
    def initialize(offset,n) @offset=offset; @strlen=n                      end
    def sizeof()            @strlen                                      end
    def CString.granu()     1                                            end
    def to_sInternal(ofs,nest=0) 
        [sprintf("'%s' (%s)\n",@value,self.class.to_s[9..-1]),ofs+@strlen]             end
      def set(v)    @value = v;                                          end
      def get()     @value;                                              end
      def toBin()   [@value].pack "a#{@strlen}";                         end
      def fromBin(bin,pos)
        @value,=bin[pos,@strlen].unpack("a#{@strlen}"); @strlen + pos 
      end
  end


  def CStruct.cT2rbT(n)  n[0]=n[0,1].upcase; n.gsub! /\s+/,"_";  n        end
  def CStruct.defBaseT(name,sizeof,signed)
    fmt=signed ? ["","c","s","","l"][sizeof] : ["","C","S","","L"][sizeof]
    cT2rbT name
    d = <<-"END"
    class #{name} < BaseT
      def initialize(offset) @offset=offset; @value=0                        end
      def each()                                                          end
      def #{name}.sizeof()    #{sizeof}                                   end
      def #{name}.granu()     #{sizeof}                                   end
      def to_sInternal(ofs,nest=0) 
        [sprintf("0x%x %d (%s)\n",@value,@value,self.class.to_s[9..-1]),ofs+#{sizeof}]          end
      def set(v)    @value = v;                                           end
      def get()     @value;                                               end
      def toBin()   [@value].pack "#{fmt}";                               end
      def inspect()   @value.inspect()                          end
      def to_s()    @value.to_s();                          end
      def to_i()    @value;                          end
      def fromBin(bin,pos)
        @value,=bin[pos,sizeof].unpack "#{fmt}"; #{sizeof} + pos 
      end
    end
    END
    CStruct.module_eval d
  end
  def CStruct.defStruct(tname,cdef)  DefStruct.new(tname,cdef)            end
  class DefStruct
    def initialize(tname,cdef)
      @init="\n"
      @defs="\n"
      @pos=0
      @granu=0
      cdef.each { |l|
        l.sub! /(\#|\/\/).*$/,""   #remove comments
        l.sub! /;\s*$/,""          #remove ';' at the end
        l.gsub! /\s*,\s*/,","      #remove space around ','
        l.strip!                   #remove leading and trailing spaces
        l.gsub! /\s+/," "          #subst group of spaces into single spaces
        case l
        when /^[{}]?\s*$/
        when /^(.+)\s(\w+)\[\s*(\d+)\s*\]/
          typ,name,cnt = $1,$2,$3.to_i
          if(typ=="char")
            addStringMember(name,cnt)
          else
            addArrayMember(typ,name,cnt)
          end
        when /^(.+)\s(\S+)/
          typ,names = $1,$2
          names.split(/,/).each{|n| addMember(typ,n)}
        else
          raise "line not recognized '#{l}'"
        end
      }
      CStruct.cT2rbT(tname)
      d=<<-"END"    
      class #{tname} < CStructBase
        def #{tname}.sizeof()  #{@pos}  
        end
        def #{tname}.granu() #{@granu}
        end
        def initialize(offset=0)    
          super(offset);   
          #{@init}; 
        end
        #{@defs}
      end
      END
      #puts d
      CStruct.module_eval d
    end
    def doAlign(typ)
      g=[CStruct.module_eval("#{typ}.granu"),CStruct.alignment].min
      @granu=[@granu,g].max
      while (@pos % g) != 0
        @init += <<-"END"
        @membn.push "gap_#{@pos}"
        @membv["gap_#{@pos}"]=Uint8_t.new(#{@pos}+offset)
        END
        @pos+=1
      end
    end
    def addStringMember(name,cnt)
      @init += <<-"END"
      @membn.push "#{name}"
      @membv["#{name}"]=CString.new(#{@pos}+offset,#{cnt})
        END
      @defs += <<-"END"
      def #{name} ()
        @membv["#{name}"].get()
      end
      END
      @pos+=cnt
    end

    def addArrayMember(typ,name,cnt)
      CStruct.cT2rbT(typ)
      doAlign(typ)
      @init += <<-"END"
      @membn.push "#{name}"
      @membv["#{name}"]=CArray.new(#{@pos}+offset,#{cnt},#{typ})
        END
      @defs += <<-"END"
      def #{name} ()
        @membv["#{name}"]
      end
      END
      @pos+=CStruct.module_eval("#{typ}.sizeof")*cnt
    end
    def addMember(typ,name)
      CStruct.cT2rbT(typ)
      doAlign(typ)
      @init += <<-"END"
      @membn.push "#{name}"
      @membv["#{name}"]=#{typ}.new(#{@pos}+offset)
      END
      @defs += <<-"END"
      def #{name}= (v)  @membv["#{name}"].set(v)    end
      def #{name} ()    @membv["#{name}"].get()     end
      END
      @pos+=CStruct.module_eval("#{typ}.sizeof")
    end
  end
  defBaseT("uint32_t",4,false)
  defBaseT("uint16_t",2,false)
  defBaseT("uint8_t", 1,false)
  defBaseT("bool",    1,false)
  defBaseT("int32_t", 4,true)
  defBaseT("int16_t", 2,true)
  defBaseT("int8_t" , 1,true)
  defBaseT("char" ,   1,true)
end

