/*****************************
 * The four programs here are :
 * 1. scale data generation program
 * 2. optimal solution determination data generation program 
 * 3. data recording program
 * 4. data reading program
******************************/
#include"headers/header.h"
using namespace std;

//The four parameters are
// maxHeight: the maximum height of the rectangle
// maxWeight: the maximum width of the rectangle
// num: the number of rectangles
// mode: the mode of the distribution
vector<rectangle> random_generate(double maxHeight,double maxWeight,int num, int mode)
{
    vector<rectangle> recs;
    //make sure the random number is different every time
    random_device rd;
    //"mt19937" is a random number generator: Mersenne Twister 19937 generator
    mt19937 gen(rd());

    //mode 0: uniform distribution(int)
    if(mode == 0)
    {
        //uniform_int_distribution: generate random integers uniformly distributed on a range
        uniform_int_distribution<> height(1, maxHeight);
        uniform_int_distribution<> weight(1, maxWeight);
        for(int i=0; i<num; i++)
            recs.push_back({(double)weight(gen),(double)height(gen),0,0});
    }
    //mode 1: normal distribution(int)
    else if(mode == 1)
    {
        //normal_distribution: generate random numbers according to a normal distribution
        //static_cast: convert a value to a specified type
        //maxHeight/2: the mean value of the normal distribution
        //maxHeight/6: the standard deviation of the normal distribution
        //There is no particular reason why the standard deviation is set this way...
        normal_distribution<> height(static_cast <double> (maxHeight/2), static_cast <double> (maxHeight/6));
        normal_distribution<> weight(static_cast <double> (maxWeight/2), static_cast <double> (maxWeight/6));
        for(int i=0; i<num; i++)
        {
            int h = static_cast <int> (height(gen));
            int w = static_cast <int> (weight(gen));
            
            //make sure the height and width are in the range
            if(h <= 0) h = 1;
            else if(h > maxHeight) h = maxHeight;
            if(w <= 0) w = 1;
            else if(w > maxWeight) w = maxWeight;

            recs.push_back({(double)w,(double)h,0,0});
        }
    }
    //mode 2: uniform distribution(double)
    else if(mode == 2)
    {
        // similar to int case
        uniform_real_distribution<> height(1, maxHeight);
        uniform_real_distribution<> weight(1, maxWeight);
        for(int i=0; i<num; i++)
            recs.push_back({weight(gen),height(gen),0,0});
    }
    //mode 3: normal distribution(double)
    else if(mode == 3)
    {
        // similar to int case
        normal_distribution<> height(static_cast <double> (maxHeight/2), static_cast <double> (maxHeight/6));
        normal_distribution<> weight(static_cast <double> (maxWeight/2), static_cast <double> (maxWeight/6));
        for(int i=0; i<num; i++)
        {
            double h,w;
            h = height(gen);
            w = weight(gen);

            // there is no need to limit the up range of the height
            if(h <= 0) h = 0.1;
            if(w <= 0) w = 0.1;
            else if(w>maxWeight) w = maxWeight;
            
            recs.push_back({w,h,0,0});
        }
    }

    return recs;
}

//The generation algorithm here is to generate certain random points on the edge of the large rectangle, and then divide the entire rectangle into n*m blocks
//Height: the height of the large rectangle
//Weight: the width of the large rectangle
//hNum: the number of rows
//wNum: the number of columns
vector<rectangle> square_generate(double Height,double Width,int hNum, int wNum)
{
    vector<rectangle> recs;
    //make sure the random number is different every time
    random_device rd;
    //"mt19937" is a random number generator: Mersenne Twister 19937 generator
    mt19937 gen(rd());

    //Use uniform distribution
    uniform_int_distribution<> height(1, Height-1);
    uniform_int_distribution<> weight(1, Width-1);

    //hp: point on the height edge
    //wp: point on the weight edge
    vector<int> hp;
    vector<int> wp;
    //push in the start and end point
    hp.push_back(0);
    wp.push_back(0);
    hp.push_back(Height);
    wp.push_back(Width);
    while(hp.size()<hNum+1)
    {
        int h = height(gen);
        //make sure the point is different
        if(find(hp.begin(), hp.end(), h) == hp.end())
            hp.push_back(h);
    }
    while(wp.size()<wNum+1)
    {
        int w = weight(gen);
        //make sure the point is different
        if(find(wp.begin(), wp.end(), w) == wp.end())
            wp.push_back(w);
    }
    //sort the points
    sort(hp.begin(), hp.end());
    sort(wp.begin(), wp.end());

    //generate the blocks
    for(int i=1; i<=hNum; i++)
        for(int j=1; j<=wNum; j++)
            recs.push_back({(double)(wp[j]-wp[j-1]),(double)(hp[i]-hp[i-1]),0,0});

    return recs;
}

//write the data to the file in the format of the test example
    /*********************
     * @ test example:
     * maxWeight
     * n 
     * weight_1 height_1
     * ...
     * weight_n height_n
    **********************/
void printrecs(vector<rectangle> recs, double maxHeight, double maxWeight, string filename)
{
    fstream outfile;
    outfile.open(DATA_FILE+filename, ios::out);

    outfile << maxWeight << " " << recs.size() << std::endl;
    for(int i=0; i<recs.size(); i++)
        outfile << recs[i].width << " " << recs[i].height << std::endl;
    
    outfile.close();
}

//read the data from the particular file into a vector<rectangle>
vector<rectangle> readRecs(std::string filename)
{
    fstream infile;
    infile.open(DATA_FILE+filename, ios::in);

    vector<rectangle> recs;
    double maxWeight;
    int n;
    
    //read the data
    infile >> maxWeight >> n;
    for(int i=0; i<n; i++)
    {
        double w,h;
        infile >> w >> h;
        recs.push_back({w,h,0,0});
    }
    //close the file
    infile.close();
    return recs;
}