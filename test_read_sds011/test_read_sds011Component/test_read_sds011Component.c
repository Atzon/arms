#include "legato.h"
#include "le_tty.h"

COMPONENT_INIT
{
    int fd = le_tty_Open( "/dev/ttyHS0", O_RDWR | O_NOCTTY | O_NDELAY );
    le_tty_SetBaudRate( fd, LE_TTY_SPEED_9600 );

    char * byte;
    char * lastbyte;

    byte = malloc( sizeof(char) );
    lastbyte = malloc( sizeof(char) );

    * byte = 0x00;

    char * buffer;
    buffer = malloc( 6 * sizeof(char) );

    int pm_25;
    int pm_100;

    while(1) {
    	printf("%x\n", * byte);
    	* lastbyte = * byte;
    	read( fd, byte, 1 );

    	if( * lastbyte == 0xaa && * byte == 0xc0 ) {
    		read( fd, buffer, 6 );
    		pm_25 = buffer[0] + 256 * buffer[1];
    		pm_100 = buffer[2] + 256 * buffer[3];

			printf("PM2.5: %.1f, PM10: %.1f\n", (double)pm_25 / 10.0, (double)pm_100 / 10.0);
    	}
//    	sleep(1);
    }
}
