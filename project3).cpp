#include <iostream>
#include <cmath>
#include <algorithm>  

using namespace std;

int main()
{
    double x[24] = {3,1.5,-3,-4,2.5,12,-3.5,-2.5,-1.5,-2.5,3.5,1.5,0.5,-5,6,-4,0,-5.5,-1,-2,4,-1,-5,-4.5};
    double y[24] = {8.5,5,2.5,4,3.5,3,6.5,-8.5,-10,-8,1.5,1,1.5,-4.5,-2.5,1,-1,0.5,3,-0.5,-1,1,1.5,2};
    
    double xc[9] = {1.5,-1,3,-5,11,-1,-5-4,6};
    double yc[9] = {0,-6,2,6,3,3,4,-2,10.5};

    double R[9] = {0.9,1.1,1.7,2.1,2.3,2.6,3.1,3.6,4.1};
    double tempR[9];
    double r ;
    
    double globalCount=0;
    int count = 0;
    do {
    count = 0;
    for (int i = 0; i < 24; i++)
    {
        for (int k = 0; k < 9; k++)
        {
            r = sqrt((x[i]-xc[k])*(x[i]-xc[k]) + (y[i]-yc[k])*(y[i]-yc[k]));
            if (r < R[k]){
                count++;
                break;;
                //cout<<x[i]<<" "<<y[i]<<endl;
                
            }
            
        }
       
        
    }
    if (count>globalCount){
        globalCount = count; 
        copy(R,R+9,tempR);
    } 

    
    //cout<<"pokriti: "<<count<<endl;
    }while(next_permutation(R, R+9));

    cout<<"global count: "<<globalCount<<endl;

    cout<<"tempR : ";
    for (int i = 0; i < 9; i++)
    {
        cout<< tempR[i]<<" ";
    }
    cout<<endl;

    return 0;
}
