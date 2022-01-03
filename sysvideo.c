#include "types.h"
#include "defs.h"
#include "memlayout.h"


int sys_getch(void) {
    return consoleget();
}

// TODO: Implement your system call for switching video modes (and any other video-related syscalls)
// in here.

int sys_vgamode(void) { //Sets VGA mode to 0x13 (320x200 16bit colour)
    return consolevgamode(0x13);    
}

int sys_textmode(void) { //sets VGA mode to 0x03 (text mode)
    return consolevgamode(0x03);
}

int sys_setpixel(void) //Sets field to black
{
    int x;
    int y;
    int colour;

    argint(0, &x);
    argint(1, &y);
    argint(2, &colour);

    uchar* location = P2V((uchar*)0xA0000 + 320 * y + x);
    *location = colour;
    return 0;
}

int sys_drawline(void) //Using bresenham's line drawing algorithm
{
    int x0, y0, x1, y1, colour, dx, dy, sx, sy, err, e2;

	argint(0, &x0);
	argint(1, &y0);
	argint(2, &x1);
	argint(3, &y1);
	argint(4, &colour);

    if ((x1 - x0) < 0)  //Because abs doesn't exist in XV6 this has the same effect as abs(x1 - x0) as required by bresenham's algorithm
    {
        dx = (x1 - x0);
        dx *= -1;
    }
    else
    {
        dx = (x1 - x0);
    }
    
    if ((y1 - y0) < 0) //Because abs doesn't exist in XV6 this has the same effect as abs(y1 - y0) as required by bresenham's algorithm
    {
        dy = (y1 - y0);
        dy *= -1;
    }
    else
    {
        dy = (y1 - y0);
    }

    err = dx - dy;

    if (x0 < x1)
    {
        sx = 1;
    }

    else
    {        
       dx  = -1;
    }
    
    if (y0 < y1)
    {
        sy = 1;
    }
    else
    {
        sy = -1;
    }

    for (int i = 0; i < 50; i++)
    {
        e2 = 2 * err;
        uchar* location = P2V((uchar*)0xA0000 + 320 * y0 + x0);

        if (x0 == x1 && y0 == y1)
        {
            break;
        }

        if (e2 > -dy)
        {
            err = err - dy;
            x0 = x0 + sx;
        }

        if (e2 < dx)
        {
            err = err + dx;
            y0 = y0 + sy;
        }

        *location = colour;
    }

    return 0;

}

