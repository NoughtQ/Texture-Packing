/*****************************************************
 * This file is used to implement the BL algorithm and BL_change algorithm
 * 
 * But my implementation of the BL algorithm here does not fully restore the idea of ​​the algorithm.
 * I did not place the objects as far as possible in the lower left position. 
 * I could only ensure that the y coordinate of each rectangle is as small as possible 
 * and the x coordinate is aligned with the corresponding leftmost coordinate point.
 * 
 * The BL_change algorithm is just adjust the placement logic of the rectangle based on the BL algorithm
******************************************************/
#include"headers/header.h"
#include<queue>
#define Infinite 1000000000
using namespace std;

// sort the recs by width, from large to small
bool cmpRecWidth(rectangle a, rectangle b)
{
    return a.width > b.width;
}
// sort the recs by weight, from large to small
// The weight is defined as the height divided by the width
// In this way, we can arrange the thin rectangles as early as possible
bool cmpRecWeight(rectangle a, rectangle b)
{
    return a.height/a.width > b.height/b.width;
}

//"*recs": The address passed in is to store coordinate information
double BL(vector<rectangle> *recs, double width, bool isDebug, string debugFile)
{
    ofstream debug;
    debug.open(debugFile,ios::out);

    //initialize
    //Using list to store the upBound, because we need to insert and delete elements frequently
    list<POINT> upBound;
    //upBound only record the left up point of the rectangle
    //The storage order of upBound is from left to right
    upBound.push_back({width,0,0});//the bound of the rightmost
    upBound.push_back({0,0,width});//the initial point
    int maxHeight=0;

    //sort the recs by width, from large to small
    sort((*recs).begin(),(*recs).end(),cmpRecWidth);
    
    //Place rectangles in order
    int cnt = 0;
    while(cnt < (*recs).size())
    {
        //initialize
        double height=Infinite;
        auto rightPoint = upBound.begin();
        int pointCase=0;
        
        //Step 1: Find the shortest rec that meets the requirements. 
        //        If they are equal, the leftmost one takes priority.
        for(auto p=upBound.begin(); p!=upBound.end(); p++)
        {
            //If placed at point p, bound means the left boundary
            double bound = (*p).x + (*recs)[cnt].width;
            //Case1: the width of the rec is less than the width of the current point
            if((*recs)[cnt].width <= (*p).width)
            {
                //If the height of the current point is lower than the previous one
                if(height >= (*p).y)
                {
                    //Update the height of the rec
                    height = (*p).y;
                    rightPoint = p;
                    pointCase = 1;
                }
            }
            //Case2: the rec can be placed in the current point
            else if (bound <= width) 
            {
                //If there is no rec that can block the rec, the flag is true
                bool flag=true;
                //Check if there is a rec that can block the rec
                for(auto it=p; it!=upBound.begin(); it--)
                {
                    if((*it).x < bound)
                    {
                        if((*it).y > (*p).y)
                        {
                            flag = false;
                            break;
                        }
                    }
                }
                //If there is no rec that can block the rec, 
                //and the height of the current point is lower than the previous one
                if(flag)
                {
                    if(height >= (*p).y)
                    {
                        height = (*p).y;
                        rightPoint = p;
                        pointCase = 2;
                    }
                }
            }
            
        }
        
        //Step 2: Place rec according to the situation and update upBound
        auto p = rightPoint;
        double bound = (*p).x + (*recs)[cnt].width;
        //Update Boundary
        
        //Case 1:
        if(pointCase==1)
        {
            //Prevent zero-width lines from appearing
            if((*p).width-(*recs)[cnt].width > 0)
                upBound.insert(p,{(*p).x+(*recs)[cnt].width, (*p).y, (*p).width-(*recs)[cnt].width});
            upBound.insert(p, {(*p).x, (*p).y+(*recs)[cnt].height, (*recs)[cnt].width});
            //If the rec is higher, update maxHeight
            if((*p).y + (*recs)[cnt].height > maxHeight)
                maxHeight = (*p).y + (*recs)[cnt].height;
            
            //update the rec location
            (*recs)[cnt].x1 = (*p).x;
            (*recs)[cnt].y1 = (*p).y;
            cnt++;   
            
            //delete the current point
            upBound.remove(*p);
        }
        //Case2
        else if(pointCase==2)
        {
            //store the point that need to be deleted
            vector<POINT> kill;
            //Check all points on the right side in turn
            for(auto it=p; it!=upBound.begin(); it--)
            {
                //The goal is to find a rectangle that is not completely covered 
                //or a point that is just not covered.
                if((*it).x < bound)
                {
                    //Not fully covered rec
                    if ((*it).x + (*it).width >= bound)
                    {
                        //update the rec location
                        (*recs)[cnt].x1 = (*p).x;
                        (*recs)[cnt].y1 = (*p).y;
                        if((*p).y + (*recs)[cnt].height > maxHeight)
                            maxHeight = (*p).y + (*recs)[cnt].height;   
                        
                        //Prevent zero-width lines from appearing
                        if((*it).x+(*it).width-bound > 0)
                            upBound.insert(p,{bound, (*it).y, (*it).x+(*it).width-bound});
                        upBound.insert(p,{(*p).x, (*p).y+(*recs)[cnt].height, (*recs)[cnt].width});
                        kill.push_back(*it);
                        break;
                    }
                    else
                        kill.push_back(*it);
                }
                //The point that is just not covered
                else if((*it).x == bound)
                {
                    //update the rec location
                    (*recs)[cnt].x1 = (*p).x;
                    (*recs)[cnt].y1 = (*p).y;
                    if((*p).y + (*recs)[cnt].height > maxHeight)
                        maxHeight = (*p).y + (*recs)[cnt].height;
                    upBound.insert(p,{(*p).x, (*p).y+(*recs)[cnt].height, (*recs)[cnt].width});
                    it--;
                    break; 
                }
                else
                    break;
            }
            //delete the point that need to be deleted
            for(auto it=kill.begin(); it!=kill.end(); it++)
            {
                //If debug mode is turned on, output the information of the deleted points
                if(isDebug)
                    debug << "kill.x: " << (*it).x << " kill.y: " << (*it).y << " width: " << (*it).width << endl;
                upBound.remove(*it);
            }
            if(isDebug)
                debug << endl;
            cnt++;
        }
        else cnt++;
        //If debug mode is turned on, output the information of the upBound step by step
        if(isDebug)
        {
            debug << "cnt:" << cnt << endl;
            for(auto it=upBound.begin(); it!=upBound.end(); it++)
                debug << "x: " << (*it).x << " y: " << (*it).y << " width: " << (*it).width << endl;
            debug << endl;
        }

    }

    //If debug mode is turned on, output the information of the all the recs
    if(isDebug)
    {
        debug << "maxHeight: " << maxHeight << endl;
        for(int i=0; i<(*recs).size(); i++)
            debug << "x1: " << (*recs)[i].x1 << " y1: " << (*recs)[i].y1 << " width: " << (*recs)[i].width << " height: " << (*recs)[i].height << endl;
    }

    return maxHeight;
}

//"*recs": The address passed in is to store coordinate information
double BL_change(vector<rectangle> *recs, double width, bool isDebug, string debugFile)
{
    ofstream debug;
    debug.open(debugFile,ios::out);

    //initialize
    //Using list to store the upBound, because we need to insert and delete elements frequently
    list<POINT> upBound;
    //upBound only record the left up point of the rectangle
    //The storage order of upBound is from left to right
    upBound.push_back({width,0,0});//the bound of the rightmost
    upBound.push_back({0,0,width});//the initial point
    int maxHeight=0;

    //Classify the rectangles, 
    //putting all those greater than half the width into one category, 
    //and the rest into another category
    vector<rectangle> wideRecs, narrowRecs;
    for(int i=0; i<(*recs).size(); i++)
    {
        if((*recs)[i].width >= width/2)
            wideRecs.push_back((*recs)[i]);
        else
            narrowRecs.push_back((*recs)[i]);
    }
    //sort by width(decreasing order)
    sort(wideRecs.begin(),wideRecs.end(),cmpRecWidth);
    //sort by weight(increasing order)
    sort(narrowRecs.begin(),narrowRecs.end(),cmpRecWeight);
    
    //Place wideRecs in order
    int cnt = 0;
    while(cnt < wideRecs.size())
    {
        //Due to their properties, it is only possible to place it on the far left.
        //So put them is easy and fast
        auto p1 = upBound.end();
        p1--;
        if((*p1).width-wideRecs[cnt].width > 0)
            upBound.insert(p1,{(*p1).x+wideRecs[cnt].width, (*p1).y, (*p1).width-wideRecs[cnt].width});
        upBound.insert(p1,{(*p1).x,(*p1).y+wideRecs[cnt].height, wideRecs[cnt].width});
        upBound.remove(*p1);

        wideRecs[cnt].x1 = (*p1).x;
        wideRecs[cnt].y1 = (*p1).y;
        cnt++;

        //If debug mode is turned on, 
        //output the information of the upBound step by step
        if(isDebug)
        {
            debug << "cnt:" << cnt << endl;
            for(auto it=upBound.begin(); it!=upBound.end(); it++)
            {
                debug << "x: " << (*it).x << " y: " << (*it).y << " width: " << (*it).width << endl;
            }
            debug << endl;
        }
    }

    //Place narrowRecs in order
    cnt = 0;
    while(cnt < narrowRecs.size())
    {
        //initialize
        double height=Infinite;
        auto rightPoint = upBound.begin();
        int pointCase=0;
        
        //same as BL, first find the proper place 
        for(auto p=upBound.begin(); p!=upBound.end(); p++)
        {
            double bound = (*p).x + narrowRecs[cnt].width;
            //case1:
            if(narrowRecs[cnt].width <= (*p).width)
            {
                //If the height of the current point is lower than the previous one
                if(height >= (*p).y)
                {
                    //Update the height of the rec
                    height = (*p).y;
                    rightPoint = p;
                    pointCase = 1;
                }
            }
            //case2:
            else if (bound <= width) 
            {
                //If there is no rec that can block the rec, the flag is true
                bool flag=true;
                //Check if there is a rec that can block the rec
                for(auto it=p; it!=upBound.begin(); it--)
                {
                    if((*it).x < bound)
                    {
                        if((*it).y > (*p).y)
                        {
                            flag = false;
                            break;
                        }
                    }
                }
                //If there is no rec that can block the rec, 
                //and the height of the current point is lower than the previous one
                if(flag)
                {
                    if(height >= (*p).y)
                    {
                        height = (*p).y;
                        rightPoint = p;
                        pointCase = 2;
                    }
                }
            }
            
        }
        
        //simular to BL algorithm, 
        //but this time we need to consider Case 3: we need to add a new line
        auto p = rightPoint;
        double bound = (*p).x + narrowRecs[cnt].width;
        //update the upBound
        //case 1
        if(pointCase==1)
        {
            //Prevent zero-width lines from appearing
            if((*p).width-narrowRecs[cnt].width > 0)
                upBound.insert(p,{(*p).x+narrowRecs[cnt].width, (*p).y, (*p).width-narrowRecs[cnt].width});
            upBound.insert(p, {(*p).x, (*p).y+narrowRecs[cnt].height, narrowRecs[cnt].width});
            //If the rec is higher, update maxHeight
            if((*p).y + narrowRecs[cnt].height > maxHeight)
                maxHeight = (*p).y + narrowRecs[cnt].height;
            
            //update the rec location
            narrowRecs[cnt].x1 = (*p).x;
            narrowRecs[cnt].y1 = (*p).y;
            cnt++;   
            
            upBound.remove(*p);
        }
        //case 2
        else if(pointCase==2)
        {
            vector<POINT> kill;
            //Check all points on the right side in turn
            for(auto it=p; it!=upBound.begin(); it--)
            {
                if((*it).x < bound)
                {
                    //Not fully covered rec
                    if ((*it).x + (*it).width >= bound)
                    {
                        //update the rec location
                        narrowRecs[cnt].x1 = (*p).x;
                        narrowRecs[cnt].y1 = (*p).y;
                        //If the rec is higher, update maxHeight
                        if((*p).y + narrowRecs[cnt].height > maxHeight)
                            maxHeight = (*p).y + narrowRecs[cnt].height;   
                        
                        if((*it).x+(*it).width-bound > 0)
                            upBound.insert(p,{bound, (*it).y, (*it).x+(*it).width-bound});
                        upBound.insert(p,{(*p).x, (*p).y+narrowRecs[cnt].height, narrowRecs[cnt].width});
                        kill.push_back(*it);
                        break;
                    }
                    else
                        kill.push_back(*it);
                }
                //The point that is just not covered
                else if((*it).x == bound)
                {
                    //update the rec location
                    narrowRecs[cnt].x1 = (*p).x;
                    narrowRecs[cnt].y1 = (*p).y;
                    //If the rec is higher, update maxHeight
                    if((*p).y + narrowRecs[cnt].height > maxHeight)
                        maxHeight = (*p).y + narrowRecs[cnt].height;
                    upBound.insert(p,{(*p).x, (*p).y+narrowRecs[cnt].height, narrowRecs[cnt].width});
                    it--;
                    break; 
                }
                else
                    break;
            }
            //delete the point that need to be deleted
            for(auto it=kill.begin(); it!=kill.end(); it++)
            {
                //If debug mode is turned on, output the information of the deleted points
                if(isDebug)
                    debug << "kill.x: " << (*it).x << " kill.y: " << (*it).y << " width: " << (*it).width << endl;
                upBound.remove(*it);
            }
            if(isDebug)
                debug << endl;
            cnt++;
        }
        //Case 3: add a new line
        //(That is, at the current highest height, place the rectangle on the far left)
        else
        {
            vector<POINT> kill;
            //Record all points that need to be deleted
            for(auto p=upBound.begin(); p!=upBound.end(); p++)
            {
                if((*p).x < narrowRecs[cnt].width)
                {
                    kill.push_back(*p);
                    if((*p).x+(*p).width-narrowRecs[cnt].width > 0)
                        upBound.insert(p,{narrowRecs[cnt].width, (*p).y, (*p).x+(*p).width-narrowRecs[cnt].width});
                }
            }
            //delete the point that need to be deleted
            debug << "***********************" << endl;//Used to mark case3
            for(auto it=kill.begin(); it!=kill.end(); it++)
            {
                if(isDebug)
                    debug << "kill.x: " << (*it).x << " kill.y: " << (*it).y << " width: " << (*it).width << endl;
                upBound.remove(*it);
            }
            if(isDebug)
                debug << endl;
            upBound.push_back({0,maxHeight+narrowRecs[cnt].height,narrowRecs[cnt].width});
            maxHeight += narrowRecs[cnt].height;
            cnt++;
        }
        //If debug mode is turned on, output the information of the upBound step by step        
        if(isDebug)
        {
            debug << "cnt:" << cnt << endl;
            for(auto it=upBound.begin(); it!=upBound.end(); it++)
                debug << "x: " << (*it).x << " y: " << (*it).y << " width: " << (*it).width << endl;
            debug << endl;
        }

    }

    //Merge the wideRecs and narrowRecs
    for(int i=0; i<wideRecs.size(); i++)
        (*recs)[i] = wideRecs[i];
    for(int i=0; i<narrowRecs.size(); i++)
        (*recs)[i+wideRecs.size()] = narrowRecs[i];
    
    //If debug mode is turned on, output the information of the all the recs
    if(isDebug)
    {
        debug << "maxHeight: " << maxHeight << endl;
        for(int i=0; i<(*recs).size(); i++)
        {
            debug << "x1: " << (*recs)[i].x1 << " y1: " << (*recs)[i].y1 << " width: " << (*recs)[i].width << " height: " << narrowRecs[i].height << endl;
        }
    }

    return maxHeight;
}