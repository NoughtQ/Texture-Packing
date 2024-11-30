#include"header.h"
using namespace std;

int main()
{
    fstream infile;
    infile.open("generate_in.txt", ios::in);
    
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