// Exercise 5
#include <iostream>
#include <math.h>
#include <random>

int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());
   	std::uniform_real_distribution<> d(-1.0,1.0);
	/*std::random_device rd1;*/
	double p_x,p_y;
	double N [3] = {100,1000,10000};
	for (int j=0; j<sizeof(N)/sizeof(*N); ++j)
	{
		double sum=0.0;
		for (int n=0;n<N[j];++n)
		{
			p_x = d(gen);
			p_y = d(gen);
			if (p_x*p_x+p_y*p_y<=1)
			{
				++sum;
			}
		}
		double pi=4*sum/N[j];
		std::cout<<"N="<<N[j]<< ":= Pi="<<pi<<"\n";
	}
}                                                                                                                                
