#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#define EPSILON 0.01
using namespace std;

void calculateNPV(vector<vector<float>> data, float taxRate, float discountRate){
  static int count=1;
  int year= data[0].size();
  float NPV=0;
  float CF;

  for(int i=0;i<year;i++){
    CF=((data[2][i]-data[0][i])*(1-(taxRate/100))-(data[1][i]));  // (revenue - operating cost)*(1-taxRate)-capitalCost = CashFlow (CF)
    NPV+=CF/pow((1+(discountRate/100)),i);
  }
cout<<"NPV for mine "<<count<<" is INR "<<NPV<<"Cr"<<endl;
count++;
}


float getIRR(vector<vector<float>> data, float taxRate,float IRR){
  int year= data[0].size();
  float ratio;
  float num=0;float denom=0;
  float CF;
  for(int i=0;i<year;i++){
    CF=((data[2][i]-data[0][i])*(1-(taxRate/100))-(data[1][i]));  // (revenue - operating cost)*(1-taxRate)-capitalCost = CashFlow (CF)
    num+=CF/pow((1+IRR),i);
    denom+=(-i*CF)/pow((1+IRR),i+1);
  }
  ratio=(num/denom);
  return ratio;
}


void calculateIRR(vector<vector<float>> data, float taxRate,float IRR){
  static int i=1;
  float n; // newton newtonRapshon derivative term ratio
  n = getIRR(data,taxRate,IRR);
  // Newton Rapshon Method for calculating IRR
  while(abs(n)>EPSILON){
  n=getIRR(data,taxRate,IRR);
  IRR=IRR-n;
}
cout<<"IRR for Mine "<<i<<" is "<<IRR*100<<"%"<<endl;
i++;
}

int main(){
  // initialization of mine cashflow data
  std::vector<float> taxRate{33.20,33.80,35.50}; // tax rate of different mines
  std::vector<float> discountRate{15.5,14.5,15.0}; // discount rate of different mines
  vector<vector<vector<float>>> data{            // creating a 3-D array for data store
    {{0,0,0,30,32,33,36,37,38,34,35},{100,85,30,0,0,0,0,0,0,0,0},{0,0,0,80,85,90,88,92,96,75,80}},  // mine 1 [operating cost, Capital cost, Revenue]
    {{0,0,35,30,32,33,36,37,38,34,35},{150,65,0,0,0,0,0,0,0,0,0},{0,0,65,65,95,90,76,99,88,77,94}}, // mine 2 [operating cost, Capital cost, Revenue]
    {{0,51,53,36,33,39,40,42,46,43,53},{200,0,0,0,0,0,0,0,0,0,0},{0,90,95,80,117,96,119,95,129,83,95}} // mine 3 [operating cost, Capital cost, Revenue]
  };

// Displaying the data
  for(int i=0;i<data.size();i++){
    cout<<"===================================================================================="<<endl;
    cout<<"Data for Mine "<<(i+1)<<endl;
    for(int j=0;j<data[i].size();j++){
      if(j==0){
        cout<<"Operating cost of Mine "<<(i+1)<<" is"<<endl;
      }
      if(j==1){
        cout<<"Capital cost of Mine "<<(i+1)<<" is"<<endl;
      }
      if(j==2){
        cout<<"Revenue cost of Mine "<<(i+1)<<" is"<<endl;
      }
      for(int k=0;k<data[i][j].size();k++){
        cout<<data[i][j][k]<<'\t';
      }
      cout<<endl;
    }
    cout<<"Tax rate of Mine "<<(i+1)<<" is "<<taxRate[i]<<endl;
    cout<<"Discount rate of Mine "<<(i+1)<<" is "<<discountRate[i]<<endl;
    cout<<endl;
  }

  // Calculating NPV
  for(int i=0;i<data.size();i++){
    calculateNPV(data[i],taxRate[i],discountRate[i]);
  }

// calculating IRR
  for(int i=0;i<data.size();i++){
    calculateIRR(data[i],taxRate[i],0.2);  // IRR =0.2 initial guess
  }

  return 0;
}
