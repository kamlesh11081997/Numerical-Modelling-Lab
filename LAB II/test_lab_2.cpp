#include<iostream>
#include<bits/stdc++.h>
#define EPSILON 0.001
using namespace std;

double func(double wp, double x_one, double x_two, double x_three, double x_four) 
{ 
    return x_one*wp*wp*wp + x_two*wp*wp + x_three*wp + x_four; 
    // To calculate function value at particular point wp
} 

double derivFunc(double wp, double x_one, double x_two, double x_three) 
{ 
    return x_one*3*wp*wp + x_two*2*wp + x_three; 
    // To calculate derivative function value at particular point wp
} 

void newtonRaphson(double wp, double x_one, double x_two, double x_three, double x_four) 
{ 
    double h = func(wp,x_one, x_two, x_three,x_four) / derivFunc(wp,x_one, x_two, x_three);
    while (abs(h) >= EPSILON) 
    { 
    	wp = wp - h;
        h = func(wp,x_one, x_two, x_three,x_four) / derivFunc(wp,x_one, x_two, x_three); 
   
        // x(i+1) = x(i) - f(x) / f'(x)
		// newtonRaphson code   
    } 
  
    cout << "The value of the root is : " << wp<<endl; 
} 

float alphabet_a( float size[], float strength[] ,int number){
	// function for value of a in s_one = k * 1000^-a
	float sum_strength_size = 0;
	float sum_size = 0;
	float sum_size_square = 0;
	float sum_strength = 0;
	for(int i = 0; i < number;i++){
		sum_strength_size += strength[i] * size[i];
		sum_size += size[i];
		sum_size_square += size[i] * size[i];
		sum_strength += strength[i];
	}

	float value_a = ((number * sum_strength_size) - (sum_size * sum_strength))/((number * sum_size_square) - pow(sum_size,2));
	return value_a;
}

float log_k( float size[],float strength[], int number){
	// function for value of log_k ro get k in s_one = k * 1000^-a
	float sum_strength_size = 0;
	float sum_size = 0;
	float sum_size_square = 0;
	float sum_strength = 0;
	for(int i = 0; i < number;i++){
		sum_strength_size += strength[i] * size[i];
		sum_size += size[i];
		sum_size_square += size[i] * size[i];
		sum_strength += strength[i];
	}
	
	float log_kvalue = ((sum_strength * sum_size_square) - (sum_size * sum_strength_size)) / ((number * sum_size_square) - pow(sum_size,2));
	return log_kvalue;
}
int main(){

	
	int n=4;
	int h = 3;
	int gamma = 25;
	double fs = 1.35;
	double wp = 37818.39037;
	// cout << "Enter number of data points " << endl;
	// cin >> n;
	// float strength[n];
	// float size[n]; 
	// cout << "Enter strength value " << endl;
	// for(int i = 0; i < n; i++){
	// 	cin >> strength[i];
	// 	strength[i] = log(strength[i]);
	// }
	// cout << "Enter size value " << endl;
	// for (int i = 0; i < n; i++){
	// 	cin>> size[i];
	// 	size[i] = log(size[i]);
	// }

	float x[]={15,40,65,100};
	float y[]={16,10,7,6};
	float value_a = alphabet_a(x, y, 4);
	float log_kvalue = log_k(x, y, 4);
	//cout << " Value for a is " << value_a << endl;
	//cout << " Value for log_k is " << log_kvalue << endl;
	float value_k;
	value_k = exp(log_kvalue);
	cout<<"k is: "<<value_k<<endl;
	cout<<" a is : "<<value_a<<endl;
	//cout << " Value for k is " << value_k << endl;
	float s_one;
	s_one = value_k * pow(1000, value_a);
	cout << "Value for S1 is " << s_one << endl;
	
	 // i is for varying depth and j is for varying wifth of gallery
	double coeff_1, coeff_2, coeff_3, coeff_4;
	for(int i = 200; i <= 400; i+=50){
		for(float j = 4; j <=6; j+=0.5){
			coeff_1 = (0.31 * s_one ) / h;
			coeff_2 =  (0.64 * s_one) - (fs  * gamma * i);
			coeff_3 = -1 * 2 * fs * gamma * i * j;
			coeff_4 =  -1 * fs * gamma * i * j * j;
			newtonRaphson(wp, coeff_1, coeff_2, coeff_3, coeff_4);
			//cout << coeff_1 << " "<< coeff_2 << " "<< coeff_3 << " "<<coeff_4 << " " << func(wp, coeff_1, coeff_2, coeff_3, coeff_4) << endl;
		}
	}

	
	// float x[]={15,40,65,100};
	// float y[]={16,10,7,6};

	// cout<<log_k(x,y,4)<<endl;
	// cout<<alphabet_a(x,y,4)<<endl;

	//newtonRaphson(wp, coeff_1, coeff_1, coeff_1, coeff_1)
	return 0;
}
