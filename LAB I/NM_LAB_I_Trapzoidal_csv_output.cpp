/*
Implementing trapezoidal  rule 
@Author : Kamlesh Kumar
@Roll No. : 15MI31007
*/
// Note: This program is valid for only positive power of variable

#include<iostream>
#include<iomanip>
#include<fstream>
#include<math.h>
using namespace std;


// getting co-efficient of power 'n'

	double getCoefficient(int n, double arr[]){
		return arr[n];
	}

// getting the function value

	double getValue(double arr[], double arg, int n){
		double ans=0;

		for(int i=0;i<=n;i++){
			double temp=(arr[i]*pow(arg,i));
			ans+=temp;
		}

		return ans;

	}


// Integration of polynomial function
double getIntegration(double arr[],int n, double lower_limit, double upper_limit){
		double static *integrationArray = new double[n+2];
		integrationArray[0]=0;
		for(int i=0;i<=n;i++){
				integrationArray[i+1]=arr[i]/(i+1);
			
		}
		//return integrationArray;
		return (getValue(integrationArray,upper_limit,n+1)-getValue(integrationArray,lower_limit,n+1));
	}

// getting the second derivative of function

	double getSecondDerivative(double arr[], double arg, int n){
		int order=2;
		double ans=0;
		//int n= (int) sizeof(arr)/sizeof(arr[0]);

		for(int i=0;i<=n;i++){
			double temp=(i*(i-1)*arr[i]*pow(arg,(i-order)));
			ans+=temp;
		}
		return ans;
	}

// getting the maximum value of second derivative

	double getMaxSecondDerivative(double arr[],double lower_limit,double upper_limit, int n){
		double i= lower_limit;
		double maxSecondDerivate=0;
		while(i<=upper_limit){
			double temp=getSecondDerivative(arr,i,n);
			if(temp>maxSecondDerivate){
				maxSecondDerivate=temp;
			}	

			i+=0.001;
		}

		return maxSecondDerivate;
	}





int main(){


	int n; // highest order of polynomial 
	double upper_limit, lower_limit;  // lower limit and upper limit of integral
	int interval;  // no of parts in which total area is divided
	double intergral; // total area of polnomial


	cout<<"Enter highest order of polynomial"<<endl;
	cin>>n;
	cout<<"Enter the lower limit"<<endl;
	cin>>lower_limit;
	cout<<"Enter the upper limit"<<endl;
	cin>>upper_limit;
	// cout<<"Enter the interval (n)"<<endl;
	// cin>>interval;

	double arr[n+1];

	// storing co-efficient of variable term
 	for(int i=0;i<=n;i++){
		cout<<"Enter the co-efficient of x^"<<i<<endl;
		cin>>arr[i];
	}



	// writing data to a file
	ofstream trapezoidalDataLog;
	trapezoidalDataLog.open("trapezoidalRuleOutput_csv.txt");
	//trapezoidalDataLog<<left<<"Trapezoidl Rule Calculation :"<<endl;
	trapezoidalDataLog<<left<<"S.No."<<"\t\t";
	trapezoidalDataLog<<left<<"a"<<"\t\t";
	trapezoidalDataLog<<left<<"b"<<"\t\t";
	trapezoidalDataLog<<left<<"Actual Area"<<"\t\t";
	trapezoidalDataLog<<left<<"Area Est."<<"\t\t";
	trapezoidalDataLog<<left<<"Division(n)"<<"\t\t";
	trapezoidalDataLog<<left<<"Max-Error"<<"\t\t";
	trapezoidalDataLog<<left<<"Error"<<"\t\t";
	trapezoidalDataLog<<left<<"max[a,b]f''(x)"<<endl;


for(int j=0;j<=100;j++){  // loop for different value of division : 

	interval=(j+1);  // division size

	double height= (upper_limit- lower_limit)/interval;  


// calculating integral

	intergral=0;
	intergral+=getValue(arr,lower_limit,n);
	intergral+=getValue(arr,upper_limit,n);

	for(int i=1;i<interval;i++){
		double ih= (height*i);
			intergral+=(2*getValue(arr,(lower_limit+ih),n));
	}


double maxSecondDerivate =getMaxSecondDerivative(arr,lower_limit,upper_limit,n);
double maxerror =(getMaxSecondDerivative(arr,lower_limit,upper_limit,n)*pow((upper_limit- lower_limit),3))/(12*interval*interval);
double area=intergral*(height/2);
double actualArea=getIntegration(arr,n,lower_limit,upper_limit);
double error=(area-actualArea);
cout<<"For Degree "<<n<<endl;
cout<<"For interval :"<<interval<<endl;
cout<<"For a (lower limit) "<<lower_limit<<endl;
cout<<"For b (upper limit) "<<upper_limit<<endl;
cout<<"Answer by trapezoidal rule is :"<<area<<endl;
cout<<"Second order derivative of polynomial is:"<<getSecondDerivative(arr,1,n)<<endl;
cout<<"Maximum second derivate value of polynomial in range a & b is: "<<maxSecondDerivate<<endl;
cout<<"Max Error in estimation: "<<maxerror<<endl;
cout<<"Error in estimation :"<<error<<endl;
cout<<"=============================================================================="<<endl;

// writing data to a file :

	trapezoidalDataLog<<left<<(j+1)<<"\t\t";
	trapezoidalDataLog<<left<<lower_limit<<"\t\t";
	trapezoidalDataLog<<left<<upper_limit<<"\t\t";
	trapezoidalDataLog<<left<<actualArea<<"\t\t";
	trapezoidalDataLog<<left<<area<<"\t\t";
	trapezoidalDataLog<<left<<interval<<"\t\t";
	trapezoidalDataLog<<left<<maxerror<<"\t\t";
	trapezoidalDataLog<<left<<error<<"\t\t";
	trapezoidalDataLog<<left<<maxSecondDerivate<<endl;


}









	return 0;


}
