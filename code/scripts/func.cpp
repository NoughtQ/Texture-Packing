//用于存储各种算法函数
#include"header.h"
#define Infinite 1000000

using namespace std;

bool cmpRecWidth(rectangle a, rectangle b)
{
    return a.width > b.width;
}
bool cmpRecHeight(rectangle a, rectangle b)
{
    return a.height > b.height;
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

/* double Rf_change(vector<rectangle> recs, double width, bool isDebug, string debugFile)
{
    list<POINT> upBoundR2L, upBoundL2R;
    upBoundR2L.push_back({width,0,0});//r2l final point
    upBoundL2R.push_back({0,0,0});// l2r final point
    upBoundR2L.push_back({0,0,width});//r2l start point
    upBoundL2R.push_back({width,0,width});//l2r start point
    int maxHeight=0;

    vector<rectangle> wideRecs, narrowRecs;
    for(int i=0; i<recs.size(); i++)
    {
        if(recs[i].width >= width/2)
            wideRecs.push_back(recs[i]);
        else
            narrowRecs.push_back(recs[i]);
    }
    sort(wideRecs.begin(),wideRecs.end(),cmpRecWidth);
    sort(narrowRecs.begin(),narrowRecs.end(),cmpRecWidth);

    int cnt = 0;
    while(cnt < wideRecs.size())
    {
        auto p1 = upBoundR2L.begin();
        if((*p1).width-recs[cnt].width > 0)
                upBoundR2L.insert(p1,{(*p1).x+recs[cnt].width, (*p1).y, (*p1).width-recs[cnt].width});
        upBoundR2L.insert(p1,{(*p1).x,(*p1).y+wideRecs[cnt].height, wideRecs[cnt].width});
        upBoundR2L.remove(*p1);

        auto p2 = upBoundL2R.end();

    }
} */