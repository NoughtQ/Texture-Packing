#include"headers/header.h"
using namespace std;

const string generateFile="../inputs/generate/generate_in.txt";

//For the convenience of input and implementation, only file input is supported
/**************** 
 * @ generate_in file format:
 * generateMode(decide the mode of the generation)
 * n(number of test cases you want to generate)
 * 
 * @ generateMode 1
 * maxHeight_1 maxWeight_1 num_1 mode_1 filename_1
 * ...
 * maxHeight_n maxWeight_n num_n mode_n filename_n
 * 
 * @ generateMode 2
 * Height_1 Weight_1 hNum_1 wNum_1 filename_1
 * ...
 * Height_n Weight_n hNum_n wNum_n filename_n
*****************/
int main()
{
    fstream infile;
    infile.open(generateFile, ios::in);
    
    int generateMode;
    infile >> generateMode;

    //generateMode1: random generation
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
        //generate n test cases
        for(i=0; i<n; i++)
        {
            infile >> maxHeight >> maxWeight >> num >> mode;
            infile >> filename;
            
            vector<rectangle> recs;
            //generate the rectangles
            recs = random_generate(maxHeight, maxWeight, num, mode);
            //write the data to the file
            printrecs(recs, maxHeight, maxWeight, filename); 
        }
    }
    //generateMode2: square generation
    else if(generateMode==2)
    {
        int i;
        double Height,Weight;
        int hNum,wNum,n;
        string filename;

        //generate n test cases
        infile >> n;
        for(i=0; i<n; i++)
        {
            infile >> Height >> Weight >> hNum >> wNum;
            infile >> filename;
            
            vector<rectangle> recs;
            //generate the rectangles
            recs = square_generate(Height, Weight, hNum, wNum);
            //write the data to the file
            printrecs(recs, Height, Weight, filename); 
        }
    }
    
    return 0;
}