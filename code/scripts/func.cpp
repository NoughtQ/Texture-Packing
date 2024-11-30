//用于存储各种算法函数
#include"header.h"
#include<queue>
#define Infinite 1000000

using namespace std;

bool cmpRecWidth(rectangle a, rectangle b)
{
    return a.width > b.width;
}
bool cmpRecWeight(rectangle a, rectangle b)
{
    return a.height/a.width > b.height/b.width;
}

double BL(vector<rectangle> *recs, double width, bool isDebug, string debugFile)
{
    ofstream debug;
    debug.open(debugFile,ios::out);

    //initialize
    list<POINT> upBound;
    //upBound only record the left up point of the rectangle
    //upBound 的储存要按从右到左，不然会出现全部堆叠在左侧的情况
    upBound.push_back({width,0,0});//作为最右侧的边界，防止最右侧的边界无法被覆盖
    upBound.push_back({0,0,width});
    int maxHeight=0;

    //sort the recs by width, from large to small
    sort((*recs).begin(),(*recs).end(),cmpRecWidth);
    
    int cnt = 0;
    while(cnt < (*recs).size())
    {
        double height=Infinite;
        auto rightPoint = upBound.begin();
        int pointCase=0;
        //第一步：找到最低矮的符合条件的rec，如果相等，则最左侧优先
        for(auto p=upBound.begin(); p!=upBound.end(); p++)
        {
            double bound = (*p).x + (*recs)[cnt].width;
            if((*recs)[cnt].width <= (*p).width)
            {
                if(height > (*p).y)
                {
                    height = (*p).y;
                    rightPoint = p;
                    pointCase = 1;
                }
            }
            else if (bound <= width) 
            {
                bool flag=true;
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
                if(flag)
                {
                    if(height > (*p).y)
                    {
                        height = (*p).y;
                        rightPoint = p;
                        pointCase = 2;
                    }
                }
            }
            
        }
        
        //第二步：根据情况防止rec，更新upBound
        auto p = rightPoint;
        double bound = (*p).x + (*recs)[cnt].width;
        //更新上边界
        //如果恰好在范围内
        if(pointCase==1)
        {
            if((*p).width-(*recs)[cnt].width > 0)
                upBound.insert(p,{(*p).x+(*recs)[cnt].width, (*p).y, (*p).width-(*recs)[cnt].width});
            upBound.insert(p, {(*p).x, (*p).y+(*recs)[cnt].height, (*recs)[cnt].width});
            if((*p).y + (*recs)[cnt].height > maxHeight)
                maxHeight = (*p).y + (*recs)[cnt].height;
            
            (*recs)[cnt].x1 = (*p).x;
            (*recs)[cnt].y1 = (*p).y;
            cnt++;   
            
            upBound.remove(*p);
        }
        //如果不在范围内，但也许也能放得下（当且仅当路径中有突起时放不下）
        else if(pointCase==2)
        {
            vector<POINT> kill;
            for(auto it=p; it!=upBound.begin(); it--)
            {
                if((*it).x < bound)
                {
                    //未完全覆盖的rec
                    if ((*it).x + (*it).width >= bound)
                    {
                        (*recs)[cnt].x1 = (*p).x;
                        (*recs)[cnt].y1 = (*p).y;
                        if((*p).y + (*recs)[cnt].height > maxHeight)
                            maxHeight = (*p).y + (*recs)[cnt].height;   
                        
                        if((*it).x+(*it).width-bound > 0)
                            upBound.insert(p,{bound, (*it).y, (*it).x+(*it).width-bound});
                        upBound.insert(p,{(*p).x, (*p).y+(*recs)[cnt].height, (*recs)[cnt].width});
                        kill.push_back(*it);
                        it--;it--;
                        break;
                    }
                    else
                        kill.push_back(*it);
                }
                else if((*it).x == bound)
                {
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
            for(auto it=kill.begin(); it!=kill.end(); it++)
            {
                if(isDebug)
                    debug << "kill.x: " << (*it).x << " kill.y: " << (*it).y << " width: " << (*it).width << endl;
                upBound.remove(*it);
            }
            if(isDebug)
                debug << endl;
            cnt++;
        }
        else cnt++;
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

    if(isDebug)
    {
        debug << "maxHeight: " << maxHeight << endl;
        for(int i=0; i<(*recs).size(); i++)
        {
            debug << "x1: " << (*recs)[i].x1 << " y1: " << (*recs)[i].y1 << " width: " << (*recs)[i].width << " height: " << (*recs)[i].height << endl;
        }
    }

    return maxHeight;

}

double BL_change(vector<rectangle> *recs, double width, bool isDebug, string debugFile)
{
    ofstream debug;
    debug.open(debugFile,ios::out);

    //initialize
    list<POINT> upBound;
    upBound.push_back({width,0,0});//作为最右侧的边界，防止最右侧的边界无法被覆盖
    upBound.push_back({0,0,width});
    int maxHeight=0;

    vector<rectangle> wideRecs, narrowRecs;
    for(int i=0; i<(*recs).size(); i++)
    {
        if((*recs)[i].width >= width/2)
            wideRecs.push_back((*recs)[i]);
        else
            narrowRecs.push_back((*recs)[i]);
    }
    sort(wideRecs.begin(),wideRecs.end(),cmpRecWidth);
    sort(narrowRecs.begin(),narrowRecs.end(),cmpRecWeight);
    
    //按序处理宽recs
    int cnt = 0;
    while(cnt < wideRecs.size())
    {
        auto p1 = upBound.end();
        p1--;
        if((*p1).width-wideRecs[cnt].width > 0)
            upBound.insert(p1,{(*p1).x+wideRecs[cnt].width, (*p1).y, (*p1).width-wideRecs[cnt].width});
        upBound.insert(p1,{(*p1).x,(*p1).y+wideRecs[cnt].height, wideRecs[cnt].width});
        upBound.remove(*p1);

        wideRecs[cnt].x1 = (*p1).x;
        wideRecs[cnt].y1 = (*p1).y;
        cnt++;

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

    cnt = 0;
    while(cnt < narrowRecs.size())
    {
        double height=Infinite;
        auto rightPoint = upBound.begin();
        int pointCase=0;
        //第一步：找到最低矮的符合条件的rec，如果相等，则最左侧优先
        for(auto p=upBound.begin(); p!=upBound.end(); p++)
        {
            double bound = (*p).x + narrowRecs[cnt].width;
            if(narrowRecs[cnt].width <= (*p).width)
            {
                if(height > (*p).y)
                {
                    height = (*p).y;
                    rightPoint = p;
                    pointCase = 1;
                }
            }
            else if (bound <= width) 
            {
                bool flag=true;
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
                if(flag)
                {
                    if(height > (*p).y)
                    {
                        height = (*p).y;
                        rightPoint = p;
                        pointCase = 2;
                    }
                }
            }
            
        }
        
        //第二步：根据情况防止rec，更新upBound
        auto p = rightPoint;
        double bound = (*p).x + narrowRecs[cnt].width;
        //更新上边界
        //如果恰好在范围内
        if(pointCase==1)
        {
            if((*p).width-narrowRecs[cnt].width > 0)
                upBound.insert(p,{(*p).x+narrowRecs[cnt].width, (*p).y, (*p).width-narrowRecs[cnt].width});
            upBound.insert(p, {(*p).x, (*p).y+narrowRecs[cnt].height, narrowRecs[cnt].width});
            if((*p).y + narrowRecs[cnt].height > maxHeight)
                maxHeight = (*p).y + narrowRecs[cnt].height;
            
            narrowRecs[cnt].x1 = (*p).x;
            narrowRecs[cnt].y1 = (*p).y;
            cnt++;   
            
            upBound.remove(*p);
        }
        //如果不在范围内，但也许也能放得下（当且仅当路径中有突起时放不下）
        else if(pointCase==2)
        {
            vector<POINT> kill;
            for(auto it=p; it!=upBound.begin(); it--)
            {
                if((*it).x < bound)
                {
                    //未完全覆盖的rec
                    if ((*it).x + (*it).width >= bound)
                    {
                        narrowRecs[cnt].x1 = (*p).x;
                        narrowRecs[cnt].y1 = (*p).y;
                        if((*p).y + narrowRecs[cnt].height > maxHeight)
                            maxHeight = (*p).y + narrowRecs[cnt].height;   
                        
                        if((*it).x+(*it).width-bound > 0)
                            upBound.insert(p,{bound, (*it).y, (*it).x+(*it).width-bound});
                        upBound.insert(p,{(*p).x, (*p).y+narrowRecs[cnt].height, narrowRecs[cnt].width});
                        kill.push_back(*it);
                        it--;it--;
                        break;
                    }
                    else
                        kill.push_back(*it);
                }
                else if((*it).x == bound)
                {
                    narrowRecs[cnt].x1 = (*p).x;
                    narrowRecs[cnt].y1 = (*p).y;
                    if((*p).y + narrowRecs[cnt].height > maxHeight)
                        maxHeight = (*p).y + narrowRecs[cnt].height;
                    upBound.insert(p,{(*p).x, (*p).y+narrowRecs[cnt].height, narrowRecs[cnt].width});
                    it--;
                    break; 
                }
                else
                    break;
            }
            for(auto it=kill.begin(); it!=kill.end(); it++)
            {
                if(isDebug)
                    debug << "kill.x: " << (*it).x << " kill.y: " << (*it).y << " width: " << (*it).width << endl;
                upBound.remove(*it);
            }
            if(isDebug)
                debug << endl;
            cnt++;
        }
        else
        {
            vector<POINT> kill;
            for(auto p=upBound.begin(); p!=upBound.end(); p++)
            {
                if((*p).x < narrowRecs[cnt].width)
                {
                    kill.push_back(*p);
                    if((*p).x+(*p).width-narrowRecs[cnt].width > 0)
                        upBound.insert(p,{narrowRecs[cnt].width, (*p).y, (*p).x+(*p).width-narrowRecs[cnt].width});
                }
            }
            debug << "***********************" << endl;
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

    for(int i=0; i<wideRecs.size(); i++)
    {
        (*recs)[i] = wideRecs[i];
    }
    for(int i=0; i<narrowRecs.size(); i++)
    {
        (*recs)[i+wideRecs.size()] = narrowRecs[i];
    }
    
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