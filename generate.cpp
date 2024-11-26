#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<random>
using namespace std;

typedef pair<int,int> rectangle;

vector<rectangle> generate(int maxHeight,int maxWeight,int num, int mode);
void printrecs(vector<rectangle> recs, int maxHeight, int maxWeight, string filename);


int main()
{
    //mode 0: uniform int distribution
    //mode 1：normal distribution
    int maxHeight,maxWeight,num,mode;
    string filename;
    cin >> maxHeight >> maxWeight >> num >> mode;
    cin >> filename;
    
    vector<rectangle> recs;
    recs = generate(maxHeight, maxWeight, num, mode);
    printrecs(recs, maxHeight, maxWeight, filename);

    return 0;
}

vector<rectangle> generate(int maxHeight,int maxWeight,int num, int mode)
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

    return recs;
}

void printrecs(vector<rectangle> recs, int maxHeight, int maxWeight, string filename)
{
    fstream outfile;
    outfile.open("data/"+filename, ios::out);

    outfile << maxHeight << " " << maxWeight << " " << recs.size() << std::endl;
    for(int i=0; i<recs.size(); i++)
        outfile << recs[i].first << " " << recs[i].second << std::endl;
    
    outfile.close();
}