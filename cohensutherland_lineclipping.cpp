#include<iostream>
#include<graphics.h>
# define LEFT 1
# define RIGHT 4
# define TOP 8
# define BOTTOM 2

using namespace std;

int xmin, xmax, ymin, ymax;

void rectangle_wind(int xmin, int ymin, int xmax, int ymax)
{
    int x,y;
    y=ymin;
    for(x=xmin; x<=xmax; x++)
        putpixel(x,y,WHITE);
    y=ymax;
    for(x=xmin; x<=xmax; x++)
        putpixel(x,y,WHITE);
    x=xmin;
    for(y=ymin; y<=ymax; y++)
        putpixel(x,y,WHITE);
    x=xmax;
    for(y=ymin; y<=ymax; y++)
        putpixel(x,y,WHITE);
}

int gencode(float x, float y)
{
    int code=0;
    if (x<xmin)
        code|= LEFT;
    if (x>xmax)
        code|=RIGHT;
    if (y<ymin)
        code|=TOP;
    if (y>ymax)
        code|=BOTTOM;

    return code;
}

void cohensutherland(float x1, float y1, float x2, float y2)
{
    bool done=false;
    int code1, code2;
    do {
        code1 = gencode(x1,y1);
        code2 = gencode(x2,y2);
        if (code1==0 && code2==0)
        {
            line(x1,y1,x2,y2);
            done = true;
        }
        else if ((code1 & code2)!=0)
        {
            done = true;
        }
        else if ((code1 & code2)==0 && (code1 | code2)!=0)
        {
            int codeout;
            float x,y;
            if (code1!=0)
                codeout=code1;
            else
                codeout=code2;
            if(codeout & TOP)
            {
                x = x1 + (x2-x1)*(ymin-y1)/(y2-y1);
                y = ymin;
            }
            else if(codeout & BOTTOM)
            {
                x = x1 + (x2-x1)*(ymax-y1)/(y2-y1);
                y = ymax;
            }
            else if(codeout & RIGHT)
            {
                y = y1 + (y2-y1)*(xmax-x1)/(x2-x1);
                x = xmax;
            }
            else if(codeout & LEFT)
            {
                y = y1 + (y2-y1)*(xmin-x1)/(x2-x1);
                x = xmin;
            }

            if (codeout==code1)
            {
                x1=x;
                y1=y;
                code1=gencode(x1,y1);
            }
            else
            {
                x2=x;
                y2=y;
                code1=gencode(x2,y2);
            }
        }
    }
    while(!done);

    line(x1,y1,x2,y2);
}

int main()
{
    int gd=DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    int x1,y1,x2,y2;
    cout<<"Enter xmin, ymin, xmax, ymax for rectangular window"<<endl;
    cin>>xmin>>ymin>>xmax>>ymax;
    rectangle_wind(xmin, ymin, xmax, ymax);
    cout<<"Enter x1,y1,x2,y2 for original line"<<endl;
    cin>>x1>>y1>>x2>>y2;
    line(x1,y1,x2,y2);
    cout<<"Press any key to clip line"<<endl;
    char ch;
    cin>>ch;
    cleardevice();
    rectangle_wind(xmin, ymin, xmax, ymax);
    cohensutherland(x1,y1,x2,y2);

    getch();
    closegraph();
    return 0;
}
