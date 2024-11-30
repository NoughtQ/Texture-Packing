#include"header.h"
using namespace std;

vector<rectangle> random_generate(double maxHeight,double maxWeight,int num, int mode)
{
    vector<rectangle> recs;
    random_device rd;
    mt19937 gen(rd());

    if(mode == 0)
    {
        uniform_int_distribution<> height(1, maxHeight);
        uniform_int_distribution<> weight(1, maxWeight);
        for(int i=0; i<num; i++)
            recs.push_back({(double)weight(gen),(double)height(gen),0,0});
    }
    else if(mode == 1)
    {
        normal_distribution<> height(static_cast <double> (maxHeight/2), static_cast <double> (maxHeight/6));
        normal_distribution<> weight(static_cast <double> (maxWeight/2), static_cast <double> (maxWeight/6));
        for(int i=0; i<num; i++)
        {
            int h = static_cast <int> (height(gen));
            int w = static_cast <int> (weight(gen));
            
            if(h <= 0) 
                h = 1;
            else if(h > maxHeight) 
                h = maxHeight;
            
            if(w <= 0)
                w = 1;
            else if(w > maxWeight)
                w = maxWeight;

            recs.push_back({(double)w,(double)h,0,0});
        }
    }
    else if(mode == 2)
    {
        uniform_real_distribution<> height(1, maxHeight);
        uniform_real_distribution<> weight(1, maxWeight);
        for(int i=0; i<num; i++)
            recs.push_back({weight(gen),height(gen),0,0});
    }
    else if(mode == 3)
    {
        normal_distribution<> height(static_cast <double> (maxHeight/2), static_cast <double> (maxHeight/6));
        normal_distribution<> weight(static_cast <double> (maxWeight/2), static_cast <double> (maxWeight/6));
        for(int i=0; i<num; i++)
        {
            double h,w;
            h = height(gen);
            w = weight(gen);

            if(h <= 0) 
                h = 0.1;
            if(w <= 0)
                w = 0.1;
            else if(w>maxWeight)
                w = maxWeight;
            
            recs.push_back({w,h,0,0});
        }
    }

    return recs;
}

vector<rectangle> square_generate(double Height,double Weight,int hNum, int wNum)
{
    vector<rectangle> recs;
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> height(1, Height-1);
    uniform_int_distribution<> weight(1, Weight-1);

    vector<int> hp;
    vector<int> wp;
    hp.push_back(0);
    wp.push_back(0);
    hp.push_back(Height);
    wp.push_back(Weight);
    while(hp.size()<hNum+1)
    {
        int h = height(gen);
        if(find(hp.begin(), hp.end(), h) == hp.end())
            hp.push_back(h);
    }
    while(wp.size()<wNum+1)
    {
        int w = weight(gen);
        if(find(wp.begin(), wp.end(), w) == wp.end())
            wp.push_back(w);
    }
    sort(hp.begin(), hp.end());
    sort(wp.begin(), wp.end());

    for(int i=1; i<=hNum; i++)
        for(int j=1; j<=wNum; j++)
            recs.push_back({(double)(wp[j]-wp[j-1]),(double)(hp[i]-hp[i-1]),0,0});

    return recs;
}

void printrecs(vector<rectangle> recs, double maxHeight, double maxWeight, string filename)
{
    fstream outfile;
    outfile.open("../data/"+filename, ios::out);

    /*********************
     * test example:
     * maxWeight
     * n 
     * weight_1 height_1
     * ...
     * weight_n height_n
    **********************/
    outfile << maxWeight << " " << recs.size() << std::endl;
    for(int i=0; i<recs.size(); i++)
        outfile << recs[i].width << " " << recs[i].height << std::endl;
    
    outfile.close();
}

vector<rectangle> readRecs(std::string filename)
{
    fstream infile;
    infile.open("../data/"+filename, ios::in);
    vector<rectangle> recs;
    double maxWeight;
    int n;
    infile >> maxWeight >> n;
    for(int i=0; i<n; i++)
    {
        double w,h;
        infile >> w >> h;
        recs.push_back({w,h,0,0});
    }
    infile.close();
    return recs;
}