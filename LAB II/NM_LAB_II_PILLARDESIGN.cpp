#include<iostream>
#include<bits/stdc++.h> 
#include<numeric>
#include<vector>
#include<math.h>
#include<iomanip>
#define EPSILON 0.001
using namespace std;

float arraySum(vector<int>&x){
	float sum=0;
	for(int i=0;i<x.size();i++){
		sum+=x[i];
	}
	return sum;
}

float arraySquareSum(vector<int>&x){
	float sum=0;
	for(int i=0;i<x.size();i++){
		sum+=pow(x[i],2);
	}
	return sum;
}


float arrayProductSum(vector<int>&x, vector<int>&y){
	float sum=0;
	for(int i=0;i<x.size();i++){
		sum +=x[i]*y[i];
	}
	return sum;
}


float getlnk(vector<int>&x,std::vector<int>&y){
	int n = x.size();
	float k=((arraySum(y)*arraySquareSum(x))-(arraySum(x)*arrayProductSum(x,y)))/((n*arraySquareSum(x))-pow(arraySum(x),2));
	return k;
}


float getMinusA(std::vector<int>&x,std::vector<int>&y){
	int n=x.size();
	float a=((n*arrayProductSum(x,y))-(arraySum(x)*arraySum(y)))/((n*arraySquareSum(x))-pow(arraySum(x),2));
	return a;
}


float getFx(float wp,std::vector<float> &coeff){
	return (coeff[3]*pow(wp,3)+coeff[2]*pow(wp,2)+coeff[1]*wp+coeff[0]);
}

float getDerivativeFx(float wp, std::vector<float> &coeff){
	return((3*coeff[3]*pow(wp,2))+(2*coeff[2]*wp)+ coeff[1]);
}


float newtonRapshon(float wp,std::vector<float> &coeff){

	float h=getFx(wp,coeff)/getDerivativeFx(wp,coeff);
	while(abs(h)>=EPSILON){
		h=getFx(wp,coeff)/getDerivativeFx(wp,coeff);
		wp=wp-h;
	}
	return wp;
}


std::vector<float> getCoefficient(float s1, float gamma,int D, float h, float wg, float fs){
// fs : factor of safety =1.35
std::vector<float> coeff;
float a1=0.36*s1;
float a2=((0.64*s1*h)-(fs*gamma*h*D));
float a3=(-2*fs*gamma*D*h*wg);
float a4=(-fs*gamma*D*wg*wg*h);
coeff.push_back(a4);
coeff.push_back(a3);
coeff.push_back(a2);
coeff.push_back(a1);
return coeff;
}

int main(){

	vector<int> x{15,40,65,100};  // x : Size
	vector<int> y{16,10,7,6};     // y : Strength

	int h=3;            // h : Mining Height
	int gamma=25000;       // gamma : 25kN/m^3
	float fs=1.35;
	double wp = 100; // initial guess
	float a=getMinusA(x,y);
	float k=exp(getlnk(x,y));
	cout<<" value of a is: "<<a<<endl;
	cout<<"Value of k is: "<<k<<endl;
	float s1=exp(getlnk(x,y))*pow(1000,getMinusA(x,y));   // s1: strength of a unit m^3 coal block
	cout<<"Value of S1 is :"<<s1<<endl;

	// cout<<fixed<<getlnk(x,y)<<endl;
	// cout<<geta(x,y)<<endl;


	for(int D=200;D<=400;D+=50){
		for(float wg=4;wg<=6;wg+=0.5){

			std::vector<float> coeff=getCoefficient(s1,gamma,D,h,wg,fs);
			// for(int i=0;i<coeff.size();i++){
			// 	cout<<"a"<<(i+1)<<" is"<<coeff[i]<<"\t";
			// }
			// cout<<endl;
			float wp=newtonRapshon(wp,coeff);
			cout<<"Width of pillar for D:"<<D<<" and wg: "<<wg<< " is "<<wp<<"m"<<endl;
		}
	}






	return 0;
}