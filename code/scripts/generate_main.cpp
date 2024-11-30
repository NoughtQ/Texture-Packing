#include"header.h"
using namespace std;

int main()
{
    fstream infile;
    infile.open("generate_in.txt", ios::in);
    
    int generateMode;
    infile >> generateMode;
    if(generateMode==1)
    {
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
            recs = random_generate(maxHeight, maxWeight, num, mode);
            printrecs(recs, maxHeight, maxWeight, filename); 
        }
    }
    else if(generateMode==2)
    {
        int i;
        double Height,Weight;
        int hNum,wNum,n;
        string filename;

        infile >> n;
        for(i=0; i<n; i++)
        {
            infile >> Height >> Weight >> hNum >> wNum;
            infile >> filename;
            
            vector<rectangle> recs;
            recs = square_generate(Height, Weight, hNum, wNum);
            printrecs(recs, Height, Weight, filename); 
        }
    }
    else
    {
        cout << "Invalid mode!" << endl;
    }

    return 0;
}