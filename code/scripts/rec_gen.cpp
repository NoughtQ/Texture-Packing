#include<iostream>
#include<fstream>
#include<queue>
#include<random>
using namespace std;

typedef struct RECS
{
    double width;
    double height;
} rectangle;

int main()
{
    fstream outfile;

    queue<rectangle> recs;
    random_device rd;
    mt19937 gen(rd());

    rectangle first;
    double width, height;
    int k;
    double x,y;

    cout << "width: " ;
    cin >> width;
    cout << "height: " ;
    cin >> height;
    cout << "k: " ;
    cin >> k;

    outfile.open("../inputs/rec_gen"+to_string(3*k+1)+".txt", ios::out);

    first.width = width;
    first.height = height;
    recs.push(first);
    while(recs.size() < 3*k+1)
    {
        rectangle temp = recs.front();
        recs.pop();

        if(gen()%2==1)
        {
            uniform_real_distribution<> h(0.01, temp.height-0.01);
            uniform_real_distribution<> w(0.01, temp.width-0.01);
            x = w(gen);
            y = h(gen);
            recs.push({x, y});
            recs.push({temp.width-x, y});
            recs.push({x, temp.height-y});
            recs.push({temp.width-x, temp.height-y});
        }
        else
            recs.push({temp.width, temp.height});
    }

    outfile << width <<" "<< 3*k+1 << endl;
    for(int i=0; i<3*k+1; i++)
    {
        rectangle temp = recs.front();
        recs.pop();
        outfile << temp.width << " " << temp.height << endl;
    }

    cout << "Generated successfully!" << endl;

    return 0;
}