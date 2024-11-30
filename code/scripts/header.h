#ifndef _HEARDER_
#define _HEARDER_ 0

#include<iostream>
#include<cstdbool>
#include<vector>
#include<list>
#include<algorithm>
#include<random>
#include<string>
#include<fstream>

typedef struct rectangle{
    double width;
    double height;
    double x1,y1;

    void operator=(const rectangle& other)
    {
        width = other.width;
        height = other.height;
        x1 = other.x1;
        y1 = other.y1;
    };
} rectangle;

struct POINT{
    double x;
    double y;
    double width;

    bool operator==(const POINT& other)
    {
        return x==other.x && y==other.y && width==other.width;
    };
};

bool cmpRecWidth(rectangle a, rectangle b);
double BL(std::vector<rectangle>* recs, double width, bool isDebug, std::string debugFile);
double BL_change(std::vector<rectangle>* recs, double width, bool isDebug, std::string debugFile);
std::vector<rectangle> readRecs(std::string filename);
std::vector<rectangle> random_generate(double maxHeight,double maxWeight,int num, int mode);
std::vector<rectangle> square_generate(double Height,double Weight,int hNum, int wNum);
void printrecs(std::vector<rectangle> recs, double maxHeight, double maxWeight, std::string filename);



#endif