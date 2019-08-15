/*
Implementing simpson's 1/3rd rule 
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


// finding the value of polynomial at any x i.e. f(x=a)

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


// Calculating fourth derivative of polynomial 
	double getFourthDerivative(double arr[], double arg, int n){
		int order=4;
		double ans=0;
		//int n= (int) sizeof(arr)/sizeof(arr[0]);

		for(int i=0;i<=n;i++){
			double temp=(i*(i-1)*(i-2)*(i-3)*arr[i]*pow(arg,(i-order)));
			ans+=temp;
		}
		return ans;
	}


// calculating maximum fourth derivative in [a,b]

	double getMaxFourthDerivative(double arr[],double lower_limit,double upper_limit, int n){
		double i= lower_limit;
		double maxFourthDerivative=0;
		while(i<=upper_limit){
			double temp=getFourthDerivative(arr,i,n);
			if(temp>maxFourthDerivative){
				maxFourthDerivative=temp;
			}	

			i+=0.001;
		}

		return maxFourthDerivative;
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

	ofstream simpsonsDataLog;
	simpsonsDataLog.open("simpsonsRuleOutput.txt");
	// simpsonsDataLog<<left<<"Simpsons Rule Calculation: "<<endl;
	// simpsonsDataLog<<left<<setw(17)<<"S.No.";
	// simpsonsDataLog<<left<<setw(17)<<"a";
	// simpsonsDataLog<<left<<setw(17)<<"b";
	// simpsonsDataLog<<left<<setw(17)<<"Actual Area";
	// simpsonsDataLog<<left<<setw(17)<<"Area Est.";
	// simpsonsDataLog<<left<<setw(17)<<"Division(n)";
	// simpsonsDataLog<<left<<setw(17)<<"Max-Error";
	// simpsonsDataLog<<left<<setw(17)<<"Error";
	// simpsonsDataLog<<left<<setw(17)<<"max[a,b]f''''(x)"<<endl;

	simpsonsDataLog<<left<<"S.No."<<"\t\t";
	simpsonsDataLog<<left<<"a"<<"\t\t";
	simpsonsDataLog<<left<<"b"<<"\t\t";
	simpsonsDataLog<<left<<"Actual Area"<<"\t\t";
	simpsonsDataLog<<left<<"Area Est."<<"\t\t";
	simpsonsDataLog<<left<<"Division(n)"<<"\t\t";
	simpsonsDataLog<<left<<"Max-Error"<<"\t\t";
	simpsonsDataLog<<left<<"Error"<<"\t\t";
	simpsonsDataLog<<left<<"max[a,b]f''(x)"<<endl;


for(int j=2;j<=100;j+=2){  // loop for different value of division : 

	interval=j;  // division size

	double height= (upper_limit- lower_limit)/interval;  


// calculating integral

	intergral=0;
	intergral+=getValue(arr,lower_limit,n);
	intergral+=getValue(arr,upper_limit,n);

	for(int i=1;i<interval;i++){
		double ih= (height*i);

			if(i%2!=0){
				intergral+=(4*getValue(arr,(lower_limit+ih),n));
			}
	
			else{
			intergral+=(2*getValue(arr,(lower_limit+ih),n));
		}
	}

double maxFourthDerivative =getMaxFourthDerivative(arr,lower_limit,upper_limit,n);
double maxerror =(getMaxFourthDerivative(arr,lower_limit,upper_limit,n)*pow((upper_limit- lower_limit),5))/(180*pow(interval,4));
double area=intergral*(height/3);
double actualArea=getIntegration(arr,n,lower_limit,upper_limit);
double error=(area-actualArea);
cout<<"For Degree "<<n<<endl;
cout<<"For interval :"<<interval<<endl;
cout<<"For a (lower limit) "<<lower_limit<<endl;
cout<<"For b (upper limit) "<<upper_limit<<endl;
cout<<"Answer by simpson's 1/3rd rule is :"<<area<<endl;
//cout<<"Second order derivative of polynomial is:"<<getFourthDerivative(arr,1,n)<<endl;
cout<<"Maximum second derivate value of polynomial in range a & b is: "<<maxFourthDerivative<<endl;
cout<<"Max-Error in estimation: "<<maxerror<<endl;
cout<<"Error in estimation : "<<error<<endl;
cout<<"=============================================================================="<<endl;

// writing data to a file :

	// simpsonsDataLog<<left<<setw(17)<<(j+1)/2;
	// simpsonsDataLog<<left<<setw(17)<<setprecision(0)<<lower_limit;
	// simpsonsDataLog<<left<<setw(17)<<upper_limit;
	// std::cout<<fixed;
	// simpsonsDataLog<<left<<setw(17)<<setprecision(4)<<fixed<<actualArea;
	// simpsonsDataLog<<left<<setw(17)<<area;
	// simpsonsDataLog<<left<<setw(17)<<interval;
	// simpsonsDataLog<<left<<setw(17)<<fixed<<maxerror;
	// simpsonsDataLog<<left<<setw(17)<<error;
	// simpsonsDataLog<<left<<setw(17)<<maxFourthDerivative<<endl;

	simpsonsDataLog<<left<<(j+1)/2<<"\t\t";
	simpsonsDataLog<<left<<setprecision(0)<<lower_limit<<"\t\t";
	simpsonsDataLog<<left<<upper_limit<<"\t\t";
	simpsonsDataLog<<left<<setprecision(4)<<fixed<<actualArea<<"\t\t";
	simpsonsDataLog<<left<<area<<"\t\t";
	simpsonsDataLog<<left<<interval<<"\t\t";
	simpsonsDataLog<<left<<fixed<<maxerror<<"\t\t";
	simpsonsDataLog<<left<<error<<"\t\t";
	simpsonsDataLog<<left<<maxFourthDerivative<<endl;


}


	return 0;


}
