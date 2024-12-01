#ifndef _HEARDER_
#define _HEARDER_ 0

#include<iostream>      // std::cout, std::cin
#include<cstdbool>      // bool
#include<vector>        // std::vector
#include<list>          // std::list
#include<algorithm>     // std::sort
#include<random>        // std::random_device, std::mt19937, and some other random functions
#include<string>        // std::string
#include<fstream>       // std::fstream

#define DATA_FILE "../inputs/"

//The structure of the rectangle
typedef struct rectangle{
    double width;
    double height;
    double x1,y1;

    //Overload the assignment operator
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

    //Overload the equal operator
    bool operator==(const POINT& other)
    {
        return x==other.x && y==other.y && width==other.width;
    };
};

// cmp function
bool cmpRecWidth(rectangle a, rectangle b);
bool cmpRecWeight(rectangle a, rectangle b);

// BL function
double BL(std::vector<rectangle>* recs, double width, bool isDebug, std::string debugFile);
double BL_change(std::vector<rectangle>* recs, double width, bool isDebug, std::string debugFile);

// Read and generate functions
std::vector<rectangle> readRecs(std::string filename);
std::vector<rectangle> random_generate(double maxHeight,double maxWeight,int num, int mode);
std::vector<rectangle> square_generate(double Height,double Weight,int hNum, int wNum);
void printrecs(std::vector<rectangle> recs, double maxHeight, double maxWeight, std::string filename);

#endif