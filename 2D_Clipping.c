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
