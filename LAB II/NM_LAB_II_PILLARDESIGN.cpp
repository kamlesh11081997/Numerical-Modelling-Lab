#include<iostream>
#include<numeric>
#include<vector>
#include<math.h>
#include<iomanip>
using namespace std;

float arraySum(vector<int> x){
	float sum=0;
	for(int i=0;i<x.size();i++){
		sum+=x[i];
	}
	return sum;
}

float arraySquareSum(vector<int> x){
	float sum=0;
	for(int i=0;i<x.size();i++){
		sum+=pow(x[i],2);
	}
	return sum;
}

float arraySumSquare(vector<int> x){
	float sum=0;
	for(int i=0;i<x.size();i++){
		sum+=x[i];
	}
	return (sum*sum);
}


float arrayMultSum(vector<int> x, vector<int> y){
	float sum=0;
	for(int i=0;i<x.size();i++){
		sum+=x[i]*y[i];
	}
	return sum;
}


float getlnk(vector<int>x,std::vector<int> y){
	int n = x.size();
	float k=(arraySum(y)*arraySquareSum(x)-arraySum(x)*arrayMultSum(x,y))/((n*arraySquareSum(x))-arraySumSquare(x));
	return k;
}


float geta(std::vector<int>x,std::vector<int>y){
	int n=x.size();
	float a=((n*arrayMultSum(x,y))-(arraySum(x)*arraySum(y)))/((n*arraySquareSum(x))-arraySumSquare(x));
	return (-a);
}



int main(){
	vector<int> x{15,40,65,100};
	vector<int> y{16,10,7,6};

	cout<<arraySum(x)<<endl;
	cout<<arraySum(y)<<endl;
	cout<<arraySquareSum(y)<<endl;
	cout<<arraySumSquare(y)<<endl;
	
	cout<<fixed<<exp(getlnk(x,y))<<endl;
	cout<<geta(x,y)<<endl;


	return 0;
}