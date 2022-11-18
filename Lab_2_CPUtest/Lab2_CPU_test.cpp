////////////////////////////////////////
////// 		  TEST CPU	  	       /////
///     Loop = 40,000 ops			 ///
///     count no of loops in 5sec    ///
///     byte = no between 0 - 255    ///
///////////////////////////////////////

////////////////////// Name Libraries /////////////
#include<iostream>
#include <ctime>
#include <windows.h>
#include <iomanip>
using namespace std;

//////////////////Defining states ////////////////// 
#define Add_Sub 0
#define Mul_Div 1
#define	ASMD	2

void Print_out(int var_type, int value)
{
	cout << '\n|' << setw(10) << var_type << '|' setw(10) << value << '|' << endl;
}

int calc_add(int current int calc_var)
{
	current = current + calc_var;
	return (current);
}
int calc_sub(int current int calc_var)
{
	current = current - calc_var;
	return (current);
}
int calc_div(int current int calc_var)
{
	current = current / calc_var;
	return (current);
}
int calc_mul(int current int calc_var)
{
	current = current * calc_var;
	return (current);
}
int main()
{
	int		short_int	 = 100;				         // 2bytes
	int		long_int	 = 300;						 // 4bytes
	float	single_precision_float = 543.12 ; 		 // 4bytes
	float	double_precision_float = 765.43; 		 // 8bytes

	//temp variables
	double  timer      = 0;
	int 	calc	   = 0;
	int 	loop_count = 0;
	int 	ops 	   = 0;
	
	int 	temp_sub   = 0;
	int 	temp_mul   = 0;
	int 	temp_div   = 0;
	int 	state 	   = 0;
	int 	loop       = 40000;
	double  start , end ;
	
	//	Addition/subtraction
	while (state == Add_Sub)
	{
		loop_count = 0;
		ops = 0;
		while (timer < 5)
		{
			//time_t start = time(0);
			start = GetTickCount(); 

			while (ops<loop)
				{
					temp_add = temp_add + short_int;
					temp_sub = temp_sub - short_int;
					ops = ops +1;
				}
			loop_count = loop_count + 1;
			end = GetTickCount();
			//time_t end = time(0);
			timer = difftime(end, start) * 1000.0;
		}

		print_out ( state , loop_count);
		state = Mul_Div;
	}

		
		while (calc < 1)
	{
		loop_count = 0;
		ops = 0;
		timer= 0;
		while (timer < 5)
		{
			//time_t start = time(0);
			start = GetTickCount(); 

			while (ops<loop)
				{
					temp_add = temp_add + long_int;
					temp_sub = temp_sub - long_int;
					ops = ops +1;
				}
			loop_count = loop_count + 1;
			end = GetTickCount();
			//time_t end = time(0);
			timer = difftime(end, start) * 1000.0;
		}

		cout<<"\nResult for addition and subtraction long_int = " << loop_count ;
		calc = 1;
	}
	
	
}
