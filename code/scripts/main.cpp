#include"header.h"
#include<ctime>
using namespace std;

int main()
{
    int i,generateMode;
    cout << "Please input the generate mode(1/2/3):" << endl;
    cout << "\033[34mPS:"<< endl << "mode 1(default mode): generate no file this time" << endl;
    cout << "mode 2: generate random rectangles" << endl;
    cout << "mode 3: Generates a set of rectangles that can be assembled into a complete rectangle\033[0m" << endl;
    cin >> generateMode;
    if(generateMode != 2 && generateMode != 3)
        generateMode = 1;
    if(generateMode!=1 && generate_main(generateMode))
        cout << "Generate successfully!" << endl;
    cout << "************************************" << endl;

test:   
    double width;
    string filename;
    string debugFile = "scripts/debug/debugfile";
    string recFile = "fig/recs/rectangles";

    
    fstream infile, outfile[3];
    for(i=0; i<3; i++)
        outfile[i].open(recFile+to_string(i)+".txt", ios::out);    
    
    cout << "Please input the name of the file you want to test:" << endl;
    cout << "\033[34mPS: the file should be in the \"data\" folder, and you need to give the file name including suffix\033[0m" << endl;
    cin >> filename;
    infile.open(DATA_FILE + filename, ios::in);
    infile >> width;

    vector<rectangle> recs[3];
    recs[0] = readRecs(filename);
    recs[1] = recs[0];
    recs[2] = recs[0];

    cout << "Open test mode (generate no debug information)?(Y/N)" << endl;
    char c;
    cin >> c;
    
    if(c == 'Y' || c == 'y')
    {
        cout << "Number of loop executions:" << endl;
        int k;
        cin >> k;
        
        double solution;
        clock_t start,finish;

        start = clock();
        for(i=0;i<k;i++)
        {
            solution = BL(recs, width, false, debugFile+"_BL.txt");
            if(k!=1 && i!=k-1)
                recs[0] = recs[2];
        }
        finish = clock();
        cout << "\033[31mmaxHeight(BL):" << solution << endl;
        printf("Time:%lfs\n\n",(double)(finish-start)/CLOCKS_PER_SEC);
        
        start = clock();
        for(i=0; i<k; i++)
        {
            solution = BL_change(recs+1, width, false, debugFile+"_BL_Change.txt");
            if(k!=1 && i!=k-1)
                recs[1] = recs[2];
        }
        finish = clock();
        cout << "maxHeight(BL_change):" << solution << endl;
        printf("Time:%lfs\033[0m\n\n",(double)(finish-start)/CLOCKS_PER_SEC);
    }
    else
    {
        cout << "\033[31mmaxHeight(BL):" << BL(recs, width, true, debugFile+"_BL.txt") << endl;
        cout << "maxHeight(BL_change):\033[0m" << BL_change(recs+1, width, true, debugFile+"_BL_Change.txt") << endl;
    }
    
    cout << "************************************" << endl;
    
    for(i=0; i<2; i++)
    {
        outfile[i] << width << endl;
        for(int j=0; j<recs[i].size(); j++)
        {
            outfile[i] << recs[i][j].x1 <<" "<< recs[i][j].y1 <<" "<< recs[i][j].width <<" "<< recs[i][j].height << endl;
        }
    }

    cout << "generate the fig now?(Y/N)" << endl;
    cout << "\033[34mPS: The program here calls python3 through the system function. You need to make sure the matplotlib library is installed.\033[0m" << endl;
    cin >> c;
    if(c=='Y' || c=='y')
    {
        system("python3 scripts/draw.py");
        cout << "Successfully generated the figure! You can see them in \"fig\" now." << endl;
    }

    cout << "run again?(Y/N)" << endl;
    cin >> c;
    if(c=='Y' || c=='y')
    {
        goto test;
    }

    return 0;
}