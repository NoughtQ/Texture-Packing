#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<random>
using namespace std;

typedef pair<double,double> rectangle;

vector<rectangle> generate(double maxHeight,double maxWeight,int num, int mode);
void printrecs(vector<rectangle> recs, double maxHeight, double maxWeight, string filename);


int main()
{
    fstream infile;
    infile.open("../test/generate_in.txt", ios::in);
    
    //mode 0: uniform int distribution
    //mode 1：normal distribution(int)
    //mode 2: uniform real distribution
    //mode 3: normal distribution(double)
    int i;
    double maxHeight,maxWeight;
    int num,mode,n;
    string filename;

    infile >> n;
    for(i=0; i<n; i++)
    {
        infile >> maxHeight >> maxWeight >> num >> mode;
        infile >> filename;
        
        vector<rectangle> recs;
        recs = generate(maxHeight, maxWeight, num, mode);
        printrecs(recs, maxHeight, maxWeight, filename); 
    }

    return 0;
}

vector<rectangle> generate(double maxHeight,double maxWeight,int num, int mode)
{
    vector<rectangle> recs;
    random_device rd;
    mt19937 gen(rd());

    if(mode == 0)
    {
        uniform_int_distribution<> height(1, maxHeight);
        uniform_int_distribution<> weight(1, maxWeight);
        for(int i=0; i<num; i++)
            recs.push_back(make_pair(height(gen),weight(gen)));
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

            recs.push_back(make_pair(h,w));
        }
    }
    else if(mode == 2)
    {
        uniform_real_distribution<> height(1, maxHeight);
        uniform_real_distribution<> weight(1, maxWeight);
        for(int i=0; i<num; i++)
            recs.push_back(make_pair(height(gen),weight(gen)));
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
            
            recs.push_back(make_pair(h,w));
        }
    }

    return recs;
}

void printrecs(vector<rectangle> recs, double maxHeight, double maxWeight, string filename)
{
    fstream outfile;
    outfile.open("../test/"+filename, ios::out);

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
        outfile << recs[i].second << " " << recs[i].first << std::endl;
    
    outfile.close();
}