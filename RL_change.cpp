//写了一半感觉实在有点麻烦，就不想写了...

double Rf_change(vector<rectangle> recs, double width, bool isDebug, string debugFile)
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

    //按序处理宽recs
    int cnt = 0;
    while(cnt < wideRecs.size())
    {
        auto p1 = upBoundR2L.begin();
        if((*p1).width-recs[cnt].width > 0)
                upBoundR2L.insert(p1,{(*p1).x+recs[cnt].width, (*p1).y, (*p1).width-recs[cnt].width});
        upBoundR2L.insert(p1,{(*p1).x,(*p1).y+wideRecs[cnt].height, wideRecs[cnt].width});
        upBoundR2L.remove(*p1);

        auto p2 = upBoundL2R.end();
        upBoundL2R.insert(p2,{(*p2).x-(*p2).width+recs[cnt].width, (*p2).y, recs[cnt].width});
        if((*p2).width-recs[cnt].width > 0)
                upBoundL2R.insert(p2,{(*p2).x, (*p2).y, (*p2).width-recs[cnt].width});
        upBoundL2R.remove(*p2);
    }

    //按序处理窄recs
    cnt = 0;
    int direction = 1;
    //1为r2l，0为l2r
    queue<int> level;
    int levelWidth=width;
    while(cnt < wideRecs.size())
    {
        while(levelWidth > 0)
        {
            level.push(cnt);
            levelWidth -= narrowRecs[cnt].width;
            cnt++;
        }
        level.pop();cnt--;

        int Temp;
        while(!level.empty())
        {
            Temp = level.front();
            level.pop();
            if(direction==1)
            {

            }
        }
        direction ^= 1;
    }

} 