#include "types.h"
#include "stat.h"
#include "user.h"

int main(){

    vgamode();      //Sets to videomode and changes all pixels to black
    
    for (int y = 0; y <= 200; y++)          //This loop doesn't work when I set the count to anything but y, not sure why but it works as is
    {
        for (int x = 0; x <= 320; x++)      //This loop doesn't work when I set the count to anything but x, not sure why but it works as is
        {
            setpixel(x, y, 0);
        }
    }


    for (int y = 0; y <= 100; y++)                  //Same reason for weird naming of count variable as above
    {
        drawline(0, 0+y*2, 150+y*5, 300+y*3, 1+y);  //Creates different coloured lines at different points on the screen
    }


    //textmode();
    //printf(1, "Testing");

    getch();
    exit();

}

