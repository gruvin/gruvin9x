# This project has been superseded by [opentx](http://opentx.googlecode.com/) #

The following data is likely obsolete, kept here for mostly just for historical record.

# Fixing the Aaautoo -Rreppeatt Problem #

## The Why ##

Call me clumsy or Mr. 'thumbs no fingers', but I personally find it quite difficult to hold down the rather clunky buttons on the Chinese '9X radio for less than the time it takes the stock ER/TH9X firmware to start auto-repeating. Consequently, I very often skip past the settings I want, and then back too far the other way, and on and on. I just couldn't take it any more. I could have asked Mr. TH or Mr. ER to do something about it, which I'm sure one of them probably would have ... but where was the fun in that? :-D

## The Fix ##

After about an hour of getting my head around the code in `drivers.cpp` and just how the rather impressive keypad handling is done -- all the while thinking there might be a bug -- I finally figured that the design simply didn't have a 'before first repeat' state built in at all. Once at that point, adding the required code seemed easy.

At about line 125 of drivers.cpp, here is the business end of the resulting code:

```
    case KSTATE_START:
      putEvent(EVT_KEY_FIRST(enuk));
      m_dblcnt++;
#ifdef RPTDELAY
      m_state   = KSTATE_RPTDELAY;
#else
      m_state   = 16;
#endif
      m_cnt     = 0;
      break;
#ifdef RPTDELAY
    case KSTATE_RPTDELAY: // gruvin: longer delay before first key repeat
      if(m_cnt == 24) putEvent(EVT_KEY_LONG(enuk)); // need to catch this inside RPTDELAY time
      if (m_cnt == 40) {
        m_state = 16;
        m_cnt = 0;
      }
      break;
#endif
    case 16:
```

NOTE: This code has since been replaced with a permanently enable version. (The `#ifdef RPTDELAY` ... `#endif` tags are gone.)

In essence, I've implemented a new `'m_state'` named KSTATE\_RPTDELAY, which is defined earlier in the code as ...

```
#ifdef RPTDELAY
  #define KSTATE_RPTDELAY 95 // gruvin: longer delay before key repeating starts
#endif
```

## But Wait! (Pun intended :-D) ##

A day or two later, I found that TH9X differs from ER9X in the way this is handled. I thought both versions were identical here, but I guess I either missed it, or perhaps TH made changes just recently.

TH9X includes an `m_state=32` on top of the 16, 8, 4, 2 and 1, which the code uses for incrementally increasing the auto-repeat rate -- the longer a key is held down. But there's also a longer initial delay of 640ms, vs. 480ms. For me, this is a little too long. (Pedantic, I know! :-P) I also quite like the modified timing that (I presume) ER introduced -- except that it caused(?) this lack of initial delay issue.

## Summary ##

I wanted to show my solution and code for anyone else who might be 'taking the plunge' and attempting to make code changes. Though this particular example has become permanent, without option to disable the feature, it will be generally important to use `#ifdef ... #endif` and Makefile/Compiler directives to control feature implementation choices. This will be especially important for features required physical hardware changes.

In this case, my `Makefile` is set up such that `make KEYRPT=DELAY` results in passing a `-DRPTDELAY` argument to the compiler, thus enabling my new code and allowing for my stuff to be left out entirely if not appreciated.