#include "legato.h"
#include "le_tty.h"

COMPONENT_INIT
{
    int fd = le_tty_Open("/dev/ttyHS0", O_RDWR | O_NOCTTY | O_NDELAY);
    le_tty_SetBaudRate(fd, LE_TTY_SPEED_9600);

    char buffer[256];

    while(1) {
    	read(fd, buffer, 100);

    	printf("PM2.5: %.1f, PM10: %.1f\n", (buffer[3])/10.0, (buffer[2])/10.0);

    	// Serial Data Output Frequency: 1 time/second
    	sleep(1);
    }

}
