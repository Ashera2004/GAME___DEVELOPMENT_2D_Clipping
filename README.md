# EX 6 : Two-Dimensional Transformations

## AIM

To write a c program to implement 2D Clipping of a line using Cohen Sutherland algorithm.


## ALGORITHM

Step 1: Start 

Step 2: Get the bottom-left coordinate of view port from the user. 

Step 3: Get the top-right coordinate of view port from the user. 

Step 4: Get the coordinates of 1st end point of line from the user. 

Step 5: Get the coordinates of 2nd endpoint of line from the user. 

Step 6: Print the region code of the first and second point. 

Step 7: If the points lie inside the view port, print ”The line is totally visible”. 

Step 8: If the starting point lies outside the view port, print “The line is invisible”  

Step 9: If the starting point lies inside the view port and the ending point lies outside the    

port, print “The line is partially visible”  

Step 10: Clip the line present outside the view port. 

Step 11: Draw the clipped line present inside the view port. 

Step 12: Stop


## Program :
```c
#include <stdio.h>
#include <graphics.h>
#include <conio.h>

#define LEFT   1
#define RIGHT  2
#define BOTTOM 4
#define TOP    8


int computeCode(float x, float y, float xmin, float ymin, float xmax, float ymax) {
    int code = 0;
    if (x < xmin) code |= LEFT;
    else if (x > xmax) code |= RIGHT;
    if (y < ymin) code |= BOTTOM;
    else if (y > ymax) code |= TOP;
    return code;
}

void cohenSutherlandClip(float x1, float y1, float x2, float y2,
                         float xmin, float ymin, float xmax, float ymax) {
    int code1, code2, accept, codeOut;
    float x, y;

    code1 = computeCode(x1, y1, xmin, ymin, xmax, ymax);
    code2 = computeCode(x2, y2, xmin, ymin, xmax, ymax);
    accept = 0;

    while (1) {
        if ((code1 == 0) && (code2 == 0)) {
            accept = 1; 
            break;
        } else if (code1 & code2) {
            break;  
        } else {
            if (code1 != 0)
                codeOut = code1;
            else
                codeOut = code2;

            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            } else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            } else if (codeOut & RIGHT) {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            } else {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1, xmin, ymin, xmax, ymax);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2, xmin, ymin, xmax, ymax);
            }
        }
    }

    
    setcolor(WHITE);
    rectangle(xmin, ymin, xmax, ymax);
    setcolor(RED);
    line(50, 50, 400, 300);
    outtextxy(10, 10, "BEFORE CLIPPING: RED = Original Line");
    getch();

   
    cleardevice();
    setcolor(WHITE);
    rectangle(xmin, ymin, xmax, ymax);
    outtextxy(10, 10, "AFTER CLIPPING: GREEN = Clipped Line");

    if (accept) {
        setcolor(GREEN);
        line(x1, y1, x2, y2);
    } else {
        outtextxy(150, 200, "Line is outside and not visible");
    }

    getch();
}

int main() {
    int gd = DETECT, gm;
    float xmin, ymin, xmax, ymax;

    
    xmin = 150;
    ymin = 100;
    xmax = 350;
    ymax = 250;

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    cohenSutherlandClip(50, 50, 400, 300, xmin, ymin, xmax, ymax);

    closegraph();
    return 0;
}


```

## Output :

**Before Clipping**

<img width="638" height="477" alt="GDT_exp6" src="https://github.com/user-attachments/assets/8535e628-31f8-4ba0-b574-9a668b854a60" />

**After Clipping**


<img width="638" height="478" alt="GDT_exp6_1" src="https://github.com/user-attachments/assets/9adc4c94-078c-4b01-8c00-b6819834694d" />


## Result :

Thus the program to perform line clipping by Cohen Sutherland algorithm was executed and the 
output was obtained.
