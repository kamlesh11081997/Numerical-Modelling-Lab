/*
Implementing semivariogram analysis
@Author : Kamlesh Kumar
@Roll No. : 15MI31007
*/
#include<iostream>
#include<algorithm>
#include<vector>
#define MINLAG 100;
#define ND -1;
using namespace std;


void calcaulateSemivariance(vector<vector<int>> z, string direction){


for(int lag=100;lag<=500;lag+=100)  // calculating for different lag distance
{
float semiVariance=0;
int counter=0;
int lagindex=lag/MINLAG;

for(int k=0;k<z.size();k++){  // for all rows
  if(z[k].size()>lagindex){
  for(int i=0,j=lagindex;i<(z[k].size()-lagindex),j<z[k].size();i++,j++){
    if(z[k][i]>0 && z[k][j]>0){
        counter++;
        semiVariance+=((z[k][i]-z[k][j])*(z[k][i]-z[k][j]));
      }
  }
}
}  // end for all rows
cout<<"Semivariance for direction:"<<direction<<" & lag distance : "<<lag<<" is "<<(semiVariance/(2*counter))<<endl;
} // end for lag distance
cout<<endl;

}


/* calculation for NS direction */
void calcaulateSemivarianceNS(std::vector<std::vector<int>>&v){
  std::vector<std::vector<int>>z;

  for(int i=0;i<v[0].size();i++){
      std::vector<int> temp;
    for(int j=0;j<v.size();j++){
      temp.push_back(v[j][i]);
    }
    z.push_back(temp);
  }
calcaulateSemivariance(z, "N-S");
}


/* calculation for 45 deg direction */
void calcaulateSemivariance45Deg(std::vector<std::vector<int>> &v){
int rows=v.size(); //m rows
int cols=v[0].size(); // n cols
// cout<<"rows: "<<rows<<endl;
// cout<<"cols: "<<cols<<endl;
std::vector<std::vector<int>> z;
for(int k=0;k<rows;k++){
  std::vector<int> temp;
  int i=k;
  int j=0;
  while(i<rows&&j<cols){
  //  cout<<v[i][j]<<'\t';
    temp.push_back(v[i][j]);
    i++;
    j++;
  }
  z.push_back(temp);
  //cout<<endl;
}
for(int k=1;k<cols;k++){
  std::vector<int> temp;
  int i=0;
  int j=k;
  while(j<cols && i<rows){
  //  cout<<v[i][j]<<'\t';
    temp.push_back(v[i][j]);
    i++;
    j++;
  }
  z.push_back(temp);
  //cout<<endl;
}

calcaulateSemivariance(z, "45 deg");

}

/* calculation for EW direction */
void calcaulateSemivarianceEW(std::vector<std::vector<int>>&v){
calcaulateSemivariance(v, "E-W");
}




int main(){

vector<vector<int>>v {
{44,-1,40,42,40,39,37,36,-1},
{42,-1,43,42,39,39,41,40,36},
{37,37,37,35,38,37,37,33,34},
{36,35,36,35,39,33,32,21,28},
{35,38,-1,35,37,36,36,35,-1},
{38,37,35,-1,30,-1,29,30,32}
};

calcaulateSemivarianceEW(v);
calcaulateSemivariance45Deg(v);
calcaulateSemivarianceNS(v);

  return 0;
}
