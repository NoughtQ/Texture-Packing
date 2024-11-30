#include"header.h"
using namespace std;

int main()
{
    double width;
    string filename;
    string debugFile1 = "debug1.txt";
    string debugFile2 = "debug2.txt";
    string recFile = "rectangles.txt";

    
    fstream infile, outfile;
    cin >> filename;
    infile.open("../data/" + filename, ios::in);
    outfile.open(recFile, ios::out);
    infile >> width;

    vector<rectangle> recs1 = readRecs(filename);
    vector<rectangle> recs2 = readRecs(filename);
    cout << "maxHeight(BL):" << BL(&recs1, width, true, debugFile1) << endl;
    cout << "maxHeight(BL_change):" << BL_change(&recs2, width, true, debugFile2) << endl;
    outfile << width << endl;
    for(int i=0; i<recs2.size(); i++)
    {
        outfile << recs2[i].x1 <<" "<<  recs2[i].y1 <<" "<<  recs2[i].width <<" "<<  recs2[i].height << endl;
    }


    return 0;
}