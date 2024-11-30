#include"header.h"
using namespace std;

int main()
{
    int num = 10;
    double width;
    string filename = "test.txt";
    string debugFile = "../debug.txt";
    string recFile = "../rectangles.txt";

    fstream infile, outfile;
    infile.open("../../data/" + filename, ios::in);
    outfile.open(recFile, ios::out);
    infile >> width;

    vector<rectangle> recs = readRecs(filename);
    cout << "maxHeight:" << BL(&recs, width, true, debugFile) << endl;
    outfile << width << endl;
    for(int i=0; i<recs.size(); i++)
    {
        outfile << recs[i].x1 <<" "<<  recs[i].y1 <<" "<<  recs[i].width <<" "<<  recs[i].height << endl;
    }


    return 0;
}