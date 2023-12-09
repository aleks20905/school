
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double x[24] = {3,1.5,-3,-4,2.5,12,-3.5,-2.5,-1.5,-2.5,3.5,1.5,0.5,-5,6,-4,0,-5.5,-1,-2,4,-1,-5,-4.5};
    double y[24] = {8.5,5,2.5,4,3.5,3,6.5,-8.5,-10,-8,1.5,1,1.5,-4.5,-2.5,1,-1,0.5,3,-0.5,-1,1,1.5,2};
    
    double xc[9] = {1.5,-1,3,-5,11,-1,-5-4,6};
    double yc[9] = {0,-6,2,6,3,3,4,-2,10.5};

    double R[9] = {1.7,2.3,3.1,3.6,4.1,2.6,0.9,2.1,1.1};
    double r ;
    int count = 0;
    int skip[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 

    
    for (int i = 0; i < 24; i++)
    {
        for (int k = 0; k < 9; k++)
        {
            r = sqrt((x[i]-xc[k])*(x[i]-xc[k]) + (y[i]-yc[k])*(y[i]-yc[k]));
            if (r < R[k]){
                skip[i] = 1;
                //cout<<x[i]<<" "<<y[i]<<endl;
                
            }
            
        }
        if (x[i]>1){ skip[i] = 1;} // finde where to skip all uncoverd T.
        
    }

    cout<< "skiping n: {";
    for (int i = 0; i < 24; i++) {
        cout<<skip[i]<<" ";
    }
    cout <<")"<<endl;

    double closestTo = 100;
    double closestA, closestB;
    for (int i = 0; i < 24; i++) {
        
        if (skip[i] == 0 ){
            r = sqrt((x[i]-5)*(x[i]-5) + (y[i]-10)*(y[i]-10));
            if(closestTo > r ){
                closestTo = r;
                closestA = x[i];
                closestB = y[i];
            }
                
        }   
        
    }
    cout <<"closest to (5, 10) is: ("<<closestA<<", "<< closestB <<") with distance: "<<closestTo;
 

    return 0;
}
