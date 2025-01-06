/*Collision Data */
/*author : taoufik bazine */


#ifndef COLL_H
#define COLL_H

#include "raylib.h"

Rectangle dataCol[10]={
    {166,850,278,232},//left
    {806,850,278,232},//right
    {49,448,1152,256},//middle
    {164,38,279,248},//left up
    {804,38,279,248},//right up
    {290,702,8,142},
    {932,702,8,142},
    {290,280,8,142},
    {932,280,8,142},
    {48,400,16,128} 
};

Rectangle dataDors[5]={
    {276,790,40,68}, //left
    {918,790,40,68}, //right
    {276,385,40,68}, //left up
    {918,385,40,68},  //right up
    {48,400,32,68} 
};

Rectangle dataWay[4]={
    {276,682,40,68}, //left
    {918,682,40,68}, //right
    {276,262,40,68}, //left up
    {918,262,40,68}  //right up 
};


Vector2 dataopenDr[4] = {
    {288,736}, //left
    {928,736}, //right
    {288,336}, //left up
    {928,336} //right up
};

Vector2 keys[5] = {
    {416,848}, //left
    {1088,1088}, //right
    {1136,448}, 
    {144,448},
    {176,48}
};


Rectangle obstacl[2] = {
    {144,448,96,20},
    {1136,448,96,20}
};

/*
      cR = mawaie.x<=dataCol[0].x+dataCol[0].width; 
      cL = mawaie.x>=dataCol[0].x;
      cD = mawaie.y<=dataCol[0].y+dataCol[0].height;
      cU = mawaie.y>=dataCol[0].y;

int isPlayerEnter(Rectangle R[5],Vector2 V){
    int i,a,b,c,d;

    for(i=0;i<5;i++){
    a = V.x>=R[i].x;
    b = V.y>=R[i].y;
    c = V.x <= R[i].x + R[i].width;
    d = V.y <= R[i].y + R[i].height;
        if(a&&b&&c&&d)
            return (i+1);
    }
    return 0;
}

Rectangle whereIsPlayer(Rectangle R[5],Vector2 V){
    Rectangle nul = {0,0,0,0};
    if(isPlayerEnter(R,V)){
        return R[isPlayerEnter(R,V)-1];
    }
    return nul;
}

int playerRect(Rectangle R){
    Rectangle nl = {0,0,0,0};
    int cn1 = R.x==nl.x;
    int cn2 = R.y==nl.y;
    int cn3 = R.width==nl.width;
    int cn4 = R.height==nl.height;

    if(cn1&&cn2&&cn3&&cn4)
        return 1;

    return 0;
}
*/


#endif