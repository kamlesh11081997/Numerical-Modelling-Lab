#include<iostream>
#include<bits/stdc++.h>
#define edge 9

using namespace std;
float calculateSumhl(vector<float> R,vector<float> Q,vector<vector<int>> dir, vector<vector<int>> loop, int loopNo){
float sumhl=0;
for(int i=0;i<loop[loopNo].size();i++){
  sumhl+=(R[loop[loopNo][i]-1]*Q[loop[loopNo][i]-1])*abs(Q[loop[loopNo][i]-1])*dir[loop[loopNo][i]-1][loopNo];
}
return (-sumhl);
}

float calculateSumdhl(vector<float> R,vector<float> Q,vector<vector<int>> dir, vector<vector<int>> loop, int loopNo){
float sumdhl=0;
for(int i=0;i<loop[loopNo].size();i++){
  sumdhl+=(R[loop[loopNo][i]-1]*abs(Q[loop[loopNo][i]-1]))*dir[loop[loopNo][i]-1][loopNo]*dir[loop[loopNo][i]-1][loopNo];
}
return (2*sumdhl);
}



float calculateDeltaQ(vector<float> R,vector<float> Q,vector<vector<int>> dir, vector<vector<int>> loop, int loopNo){
  float delQ=0;
  delQ=calculateSumhl(R,Q,dir,loop,loopNo)/calculateSumdhl(R,Q,dir,loop,loopNo);
return delQ;
}


int main(){
  float width,height,k;
  width=3.5; // in m
  height=4; //in m
  k=0.024; // in kg/m^3

// initial air flow guess in branch 1, 2,3,4,.. etc.
vector<float> Q{0.7, 0.2, 0, 0.2, 0.5, 0.471, 0.2, 0.671, 0.63};

// direction branch{loop1,loop2,loop3}
vector<vector<int>> dir{{1,0,0},{1,-1,0},{1,0,-1},{1,0,0},{0,1,0},{0,1,0},{0,-1,1},{0,0,1},{0,0,1}};  // direction co-efficient for each branch in different loop

// storing length of each branches
  vector<float> L{200,200,200,200,400,200,400,200,400};

// storing name of branches
vector<string> branchName{"AB","BE","EF","AF","BC","CD","DE","DG","FG"};

// storing the loop information
std::vector<vector<int>> loop{{1,2,3,4},{2,5,6,7},{3,7,8,9}};   // total 3 loops with branch information

// calculating air resistance of each brances
  vector<float> R;
  for(int i=0;i<edge;i++){
    float s=2*(width+height)*L[i]; // lateral surface area
    float a=(width*height); // corss sectional area
    float resistance=k*s/pow(a,3);  // R=ks/a^3
    R.push_back(resistance);
  }

// calculation of air flow in every branches
float dq0=1;
float dq1=1;
float dq2=1;
do{
dq0=calculateDeltaQ(R,Q,dir,loop,0);
dq1=calculateDeltaQ(R,Q,dir,loop,1);
dq2=calculateDeltaQ(R,Q,dir,loop,2);

// for loop 0
for(int i=0; i<loop[0].size(); i++)
{
  Q[loop[0][i]-1]=Q[loop[0][i]-1]+(dir[loop[0][i]-1][0]*dq0);
}
// for loop 1
for(int i=0; i<loop[1].size(); i++)
{
  Q[loop[1][i]-1]=Q[loop[1][i]-1]+(dir[loop[1][i]-1][1]*dq1);
}
// for loop 2
for(int i=0; i<loop[2].size(); i++)
{
  Q[loop[2][i]-1]=Q[loop[2][i]-1]+(dir[loop[2][i]-1][2]*dq2);
}

}while(abs(dq0)>0.001 && abs(dq1)>0.001 && abs(dq2)>0.001);


  // printing air resistance in each branch
  cout<<"Air resistance"<<endl;
  for(int i=0;i<R.size();i++){
    cout<<branchName[i]<<' '<<R[i]<<endl;
  }


// printing air flow (q) in each branch
cout<<"Air flow in difference branches"<<endl;
for(int i=0;i<Q.size();i++){
  cout<<branchName[i]<<' '<<Q[i]<<endl;
}

  return 0;
}
