#include<iostream>
#include<math.h>
using namespace std;

	double getValue(double arr[], double arg, int n){
		double ans=0;

		for(int i=0;i<=n;i++){
			double temp=(arr[i]*pow(arg,i));
			ans+=temp;
		}

		return ans;

	}  



	double getIntegration(double arr[],int n, double lower_limit, double upper_limit){
		double static *integrationArray = new double[n+2];
		integrationArray[0]=0;
		for(int i=0;i<=n;i++){
				integrationArray[i+1]=arr[i]/(i+1);
			
		}

		//return integrationArray;
		return (getValue(integrationArray,upper_limit,n+1)-getValue(integrationArray,lower_limit,n+1));
	}



int main(){
	int n;
	double lower_limit;
	double upper_limit;
	cout<<"Enter the highest order of polynomial"<<endl;
	cin>>n;
	cout<<"Enter the lower limit"<<endl;
	cin>>lower_limit;
	cout<<"Enter the upper limit"<<endl;
	cin>>upper_limit;

	double arr[n+1];

	for(int i=0;i<=n;i++){
		cout<<"Enter the co-eff of x^"<<i<<endl;
		cin>>arr[i];
	}


	double integral=getIntegration(arr,n,lower_limit,upper_limit);
	cout<<"Integral value is:"<<integral<<endl;
	return 0;
}