#include<iostream>
#include<cstdbool>
#include<vector>
#include<list>
#include<algorithm>

using namespace std;

struct REC{
    double width;
    double height;
    double x1,y1;
};
struct POINT{
    double x;
    double y;
    double width;

    bool operator==(const POINT& other)
    {
        return x==other.x && y==other.y && width==other.width;
    };
};

bool cmpRecWidth(REC a, REC b)
{
    return a.width > b.width;
}

double BL(vector<REC> recs, double width)
{
    //initialize
    list<POINT> upBound;
    //upBound only record the left up point of the rectangle
    //upBound 的储存要按从右到左，不然会出现全部堆叠在左侧的情况
    upBound.push_back({0,0,width});
    int maxHeight=0;

    //sort the recs by width, from large to small
    sort(recs.begin(),recs.end(),cmpRecWidth);
    
    int cnt = 0;
    while(cnt < recs.size())
    {
        for(auto p=upBound.begin(); p!=upBound.end(); p++)
        {
            double bound = (*p).x + recs[cnt].width;
            
            //更新上边界
            //如果恰好在范围内
            if(recs[cnt].width <= (*p).width)
            {
                if((*p).width-recs[cnt].width > 0)
                    upBound.insert(p,{(*p).x+recs[cnt].width, (*p).y, (*p).width-recs[cnt].width});
                upBound.insert(p, {(*p).x, (*p).y+recs[cnt].height, recs[cnt].width});
                if((*p).y + recs[cnt].height > maxHeight)
                    maxHeight = (*p).y + recs[cnt].height;
                
                recs[cnt].x1 = (*p).x;
                recs[cnt].y1 = (*p).y;
                cnt++;   
                
                upBound.remove(*p);
                break;
            }
            //如果不在范围内，但也许也能放得下（当且仅当路径中有突起时放不下）
            else if(bound <= width)
            {
                bool flag = true;
                vector<POINT> kill;
                for(auto it=p; it!=upBound.begin(); it--)
                {
                    if((*it).x < bound)
                    {
                        //中间突起，无法放置
                        if((*it).y > (*p).y)
                        {
                            flag = false;
                            break;
                        }
                        //未完全覆盖的rec
                        else if((*it).x + (*it).width >= bound)
                        {
                            recs[cnt].x1 = (*p).x;
                            recs[cnt].y1 = (*p).y;
                            if((*p).y + recs[cnt].height > maxHeight)
                                maxHeight = (*p).y + recs[cnt].height;   
                            
                            if((*it).x+(*it).width-bound > 0)
                                upBound.insert(p,{bound, (*it).y, (*it).x+(*it).width-bound});
                            upBound.insert(p,{(*p).x, (*p).y+recs[cnt].height, recs[cnt].width});
                            kill.push_back(*it);
                            it--;it--;
                            break;
                        }
                        else if((*it).x == bound)
                        {
                            recs[cnt].x1 = (*p).x;
                            recs[cnt].y1 = (*p).y;
                            if((*p).y + recs[cnt].height > maxHeight)
                                maxHeight = (*p).y + recs[cnt].height;
                            upBound.insert(p,{(*p).x, (*p).y+recs[cnt].height, recs[cnt].width});
                            it--;
                            break; 
                        }
                        //完全覆盖的rec
                        else
                            kill.push_back(*it);
                    } 
                    else
                        break;
                }
                //删除意味着已经放下了这个rec，因此不必考虑迭代器的维持问题
                for(auto it=kill.begin(); it!=kill.end() && flag; it++)
                {
                    cout << "x: " << (*it).x << " y: " << (*it).y << " width: " << (*it).width << endl;
                    upBound.remove(*it);
                }
                cout << endl;    
                
                if (flag)
                {
                    cnt++;
                    break;
                }
            }
        }
        for(auto it=upBound.begin(); it!=upBound.end(); it++)
        {
            cout << "x: " << (*it).x << " y: " << (*it).y << " width: " << (*it).width << endl;
        }
        cout << endl;
    }
    return maxHeight;

}

int main()
{
    vector<REC> recs = {{10,1,0,0},{9,1,0,0},{8,1,0,0},{6,1,0,0},{3,2,0,0},{5,3,0,0}};
    cout << BL(recs, 10) << endl;
    return 0;
}