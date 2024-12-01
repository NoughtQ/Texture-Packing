#include"headers/header.h"
#include<ctime>
using namespace std;

int main()
{
test:   
    int i;
    double width;
    string filename;
    //The file path of the debug information
    const string debugFile = "../outputs/BL/debug/debugfile";
    //The file path of the output rectangles information
    const string recFile = "../outputs/BL/recs/rectangles";

    //open the file
    fstream infile, outfile[2];
    for(i=0; i<1; i++)
        outfile[i].open(recFile+to_string(i)+".txt", ios::out);    
    
    //input the data test file name
    cout << "Please input the name of the file you want to test:" << endl;
    cout << "\033[34mPS: the file should be in the \"data\" folder, and you need to give the file name including suffix\033[0m" << endl;
    cin >> filename;
    infile.open(DATA_FILE + filename, ios::in);
    
    infile >> width;

    //Read the data from the file
    //recs[2] is used to store the initial data, 
    //which is used to restore the data after each test
    vector<rectangle> recs[3];
    recs[0] = readRecs(filename);
    recs[1] = recs[0];
    recs[2] = recs[0];

    cout << "Open test mode (generate no debug information)?(Y/N)" << endl;
    char c; cin >> c;
    
    //The test mode:
    if(c == 'Y' || c == 'y')
    {
        //The number of loop executions
        cout << "Number of loop executions:" << endl;
        int k; cin >> k;
        
        double solution,duration=0;
        clock_t start,finish;

        //The BL algorithm and the BL_change algorithm are executed k times respectively
        //The data is restored after each test (Except for the last test)
        //Overloaded the rec assignment operation to ensure deep restore
        for(i=0;i<k;i++)
        {
            //test the BL algorithm
            start = clock();
            solution = BL(recs, width, false, debugFile+"_BL.txt");
            finish = clock();
            duration+=(double)(finish-start)/CLOCKS_PER_SEC;
            
            //restore the data
            if(i!=k-1)
                recs[0] = recs[2];
        }
        cout << "\033[31mmaxHeight(BL):" << solution << endl;
        printf("Time:%lfs\n\n", duration);
        
        duration = 0;
        for(i=0; i<k; i++)
        {
            //test the BL_change algorithm
            start = clock();
            solution = BL_change(recs+1, width, false, debugFile+"_BL_Change.txt");
            finish = clock();
            duration+=(double)(finish-start)/CLOCKS_PER_SEC;

            //restore the data
            if(k!=1 && i!=k-1)
                recs[1] = recs[2];
        }
        cout << "maxHeight(BL_change):" << solution << endl;
        printf("Time:%lfs\033[0m\n\n", duration);
    }
    //debug mode
    else
    {
        cout << "\033[31mmaxHeight(BL):" << BL(recs, width, true, debugFile+"_BL.txt") << endl;
        cout << "maxHeight(BL_change):\033[0m" << BL_change(recs+1, width, true, debugFile+"_BL_Change.txt") << endl;
    }
    
    cout << "************************************" << endl;
    
    //write the data to the file to draw the figure
    for(i=0; i<1; i++)
    {
        outfile[i] << width << endl;
        for(int j=0; j<recs[i].size(); j++)
            outfile[i] << recs[i][j].x1 <<" "<< recs[i][j].y1 <<" "<< recs[i][j].width <<" "<< recs[i][j].height << endl;
    }

    /* cout << "generate the fig now?(Y/N)" << endl;
    cout << "\033[34mPS: The program here calls python3 through the system function. You need to make sure the matplotlib library is installed.\033[0m" << endl;
    cin >> c;
    if(c=='Y' || c=='y')
    {
        system("python3 scripts/draw.py");
        cout << "Successfully generated the figure! You can see them in \"fig\" now." << endl;
    } */

    cout << "run again?(Y/N)" << endl; cin >> c;
    if(c=='Y' || c=='y') goto test;

    return 0;
}