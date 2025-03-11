#ifndef STRUCTS_H_
#define STRUCTS_H_

struct Colour
{
    float R;
    float G;
    float B;
};

struct WorldSquare
{
    float PosX;
    float PosY;
    float Layer;
    float Size; 
    struct Colour Col;
};

#endif