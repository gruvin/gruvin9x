#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdlib.h>
#include <sys/ioctl.h>

#define DEBUG 0
/*
* 'open_port()' - Open serial port 1.
*
* Returns the file descriptor on success or -1 on error.
*/

int fd; /* File descriptor for the port */
int open_port(void)
{
  fd = open("/dev/tty.usbserial-FTCDIWIU", O_RDONLY | O_NOCTTY | O_NONBLOCK);
  if (fd == -1)
  {
    perror("open_port: Unable to open /dev/tty.usbserial-FTCDIWIU - ");
    return false;
  }
  else
  {
    
//    fcntl(fd, F_SETFL, FNDELAY); // no delay. return 0 if nothing in buffer

    struct termios options;
    tcgetattr(fd, &options);
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~CSIZE; /* Mask the character size bits */
    options.c_cflag |= CS8;    /* Select 8 data bits */
    options.c_cflag &= ~CRTSCTS; // diasble hardware flow control
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // raw input
    options.c_oflag &= ~OPOST; // raw output (just in case we do some output)
    options.c_cc[VMIN] = 0;
    options.c_cc[VTIME] = 10;     // 1 sec timeout
    tcsetattr(fd, TCSANOW, &options);
    return true;
  }  
}

char packetBuf[30];
int numPktBytes = 0;
void processByte(unsigned char c)
{
  static char lastByte = 0;
  static unsigned char inFrame = 0;

  switch (c)
  {
    case 0x7d:
        break;

    case 0x7e:
        if (lastByte == 0x7e) // then we are starting a new frame 
        {
          if (DEBUG) printf("START FRAME ");
          
          inFrame = 1;
          numPktBytes = 0;
          lastByte = 0;

        }
        else // we might have just completed capturing a frame
        {

          if (DEBUG) printf("END FRAME\n");
          
          // process the frame
          switch (packetBuf[0])
          {
            case 0xfc:
              printf("A1 Alarm\n");
              break;

            case 0xfb:
              printf("A2 Alarm\n");
              break;

            case 0xfe: // A1/A2/RSSI values
              /*
              printf("A1:%03d   A2:%03d RSSI:%udB\n", 
                  (unsigned char)packetBuf[1], (unsigned char)packetBuf[2],
                  (unsigned char)packetBuf[3]
              );
              */
              break;

            case 0xfd: // User Data packet
              if (DEBUG) printf("DATA:");
              for (int z=0; z < packetBuf[1]; z++) putchar(packetBuf[z+3]);
              if (DEBUG) printf("\n");
              fflush(stdout);
              break;

            default:
              printf("UNKNOWN FRAME TYPE\n");

          } // nested switch
        }
        break;

    default:
        if (inFrame) 
        {
          
          if (DEBUG) printf("%02x ", c);
          if (lastByte == 0x7d)
            packetBuf[numPktBytes] = c ^ 0x20;
          else
            packetBuf[numPktBytes] = c;
          numPktBytes++;

          if (numPktBytes > 30)
          {
            printf("ERROR!: packetBuf overrun!\n\n");
            exit (0);
          }
        }
  } // outer switch

  lastByte = c;
}

int main()
{
  char buffer[255];  /* Input buffer */
  int  nbytes;       /* Number of bytes read */

  if (!open_port()) exit(0);
  printf("open_port returned OK\n");
  printf("Entering main loop...\n");

  // ioctl(fd, FIONREAD, &nbytes); // how many (if any) serial bytes are available to read?

  while (1)
  {
    if ((nbytes = read(fd, buffer, 30)) > 0)
      for(int i = 0; i < nbytes; i++) 
        processByte((unsigned char)buffer[i]);
  }

  close(fd);
  printf("\nThe port closed OK\n");
}

