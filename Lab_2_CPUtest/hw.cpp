////////////////////////////////////////
////// 		  TEST CPU	  	       /////
///     Loop = 40,000 ops			 ///
///     count no of loops in 5sec    ///
///     byte = no between 0 - 255    ///
///////////////////////////////////////

//////////////////		Name Libraries 		/////////////
#include<iostream>
#include <ctime>
#include <windows.h>
#include <iomanip>
using namespace std;

//////////////////		Defining states	 	////////////////// 
#define Add_Sub 0
#define Mul_Div 1
#define	ASMD	2
#define END		3

//////////////////		Declaring Variables ///////////
	int		short_int	 = 100;				         // 2bytes
	int		long_int	 = 300;						 // 4bytes
	float	single_precision_float = 543.12 ; 		 // 4bytes
	float	double_precision_float = 765.43; 		 // 8bytes
	
	double  start , end   ;
	double  timer      = 0;
	int 	calc	   = 0;
	int 	loop_count = 0;
	int 	ops 	   = 0;
	int 	temp_sub   = 0;
	int 	temp_mul   = 0;
	int 	temp_div   = 0;
	int 	state 	   = 0;
	
	int 	loop       = 40000;
	
	
	
//////////////////		Main Function 		//////////////
int main()
{	
	if (state == Add_Sub)
	{
		print_title ( state );
		print_break ();
		/////////// Short Integer //////////
		while (timer < 5)
		{
			start = GetTickCount(); //time_t start = time(0); 

			while (ops<loop)
			{
				temp_add = calc_add (temp_add, short_int) ;
				temp_sub = calc_sub (temp_sub, short_int) ;
				ops = ops +1;
			}
			loop_count = loop_count + 1;
			end = GetTickCount(); //time_t end = time(0);
			timer = difftime(end, start) * 1000.0;
		}
		
		print_out ( "short_int" , loop_count);
		print_break();
		reset_values();
		
		/////////// Long Integer //////////
		while (timer < 5)
		{
			start = GetTickCount(); //time_t start = time(0);
			
			while (ops<loop)
			{
				temp_add = calc_add (temp_add, long_int) ;
				temp_sub = calc_sub (temp_sub, long_int) ;
				ops = ops +1;
			}
			loop_count = loop_count + 1;
			end = GetTickCount(); //time_t end = time(0);
			timer = difftime(end, start) * 1000.0;
		}
		print_out ( "long_int" , loop_count);
		print_break();
		reset_values();
		
		/////////// single_precision_float //////////
		while (timer < 5)
		{
			start = GetTickCount(); //time_t start = time(0);
			
			while (ops<loop)
			{
				temp_add = calc_add (temp_add, single_precision_float) ;
				temp_sub = calc_sub (temp_sub, single_precision_float) ;
				ops = ops +1;
			}
			loop_count = loop_count + 1;
			end = GetTickCount(); //time_t end = time(0);
			timer = difftime(end, start) * 1000.0;
		}
		print_out ( "single_precision_float" , loop_count);
		print_break();
		reset_values();
		
				/////////// double_precision_float //////////
		while (timer < 5)
		{
			start = GetTickCount(); //time_t start = time(0);
			
			while (ops<loop)
			{
				temp_add = calc_add (temp_add, double_precision_float) ;
				temp_sub = calc_sub (temp_sub, double_precision_float) ;
				ops = ops +1;
			}
			loop_count = loop_count + 1;
			end = GetTickCount(); //time_t end = time(0);
			timer = difftime(end, start) * 1000.0;
		}
		print_out ( "double_precision_float" , loop_count);
		print_break();
		reset_values();
		
		state = Mul_Div;
	}
	
	if (state == Mul_Div)
	{
		print_title ( state );
		print_break ();
		/////////// Short Integer //////////
		while (timer < 5)
		{
			start = GetTickCount(); //time_t start = time(0); 

			while (ops<loop)
			{
				temp_mul = calc_mul (temp_mul, short_int) ;
				temp_div = calc_div (temp_div, short_int) ;
				ops = ops +1;
			}
			loop_count = loop_count + 1;
			end = GetTickCount(); //time_t end = time(0);
			timer = difftime(end, start) * 1000.0;
		}
		
		print_out ( "short_int" , loop_count);
		print_break();
		reset_values();
		
		/////////// Long Integer //////////
		while (timer < 5)
		{
			start = GetTickCount(); //time_t start = time(0);
			
			while (ops<loop)
			{
				temp_mul = calc_mul (temp_mul, long_int) ;
				temp_div = calc_div (temp_div, long_int) ;
				ops = ops +1;
			}
			loop_count = loop_count + 1;
			end = GetTickCount(); //time_t end = time(0);
			timer = difftime(end, start) * 1000.0;
		}
		print_out ( "long_int" , loop_count);
		print_break();
		reset_values();
		
		/////////// single_precision_float //////////
		while (timer < 5)
		{
			start = GetTickCount(); //time_t start = time(0);
			
			while (ops<loop)
			{
				temp_mul = calc_mul (temp_mul, single_precision_float) ;
				temp_div = calc_div (temp_div, single_precision_float) ;
				ops = ops +1;
			}
			loop_count = loop_count + 1;
			end = GetTickCount(); //time_t end = time(0);
			timer = difftime(end, start) * 1000.0;
		}
		print_out ( "single_precision_float" , loop_count);
		print_break();
		reset_values();
		
				/////////// double_precision_float //////////
		while (timer < 5)
		{
			start = GetTickCount(); //time_t start = time(0);
			
			while (ops<loop)
			{
				temp_mul = calc_mul (temp_mul, double_precision_float) ;
				temp_div = calc_div (temp_div, double_precision_float) ;
				ops = ops +1;
			}
			loop_count = loop_count + 1;
			end = GetTickCount(); //time_t end = time(0);
			timer = difftime(end, start) * 1000.0;
		}
		print_out ( "double_precision_float" , loop_count);
		print_break();
		reset_values();
		
		state = ASMD;
	}
	
	if (state == ASMD)
	{
		print_title ( state );
		print_break ();
		/////////// Short Integer //////////
		while (timer < 5)
		{
			start = GetTickCount(); //time_t start = time(0); 

			while (ops<loop)
			{
				temp_add = calc_add (temp_add, short_int) ;
				temp_sub = calc_sub (temp_sub, short_int) ;
				temp_mul = calc_mul (temp_mul, short_int) ;
				temp_div = calc_div (temp_div, short_int) ;
				ops = ops +1;
			}
			loop_count = loop_count + 1;
			end = GetTickCount(); //time_t end = time(0);
			timer = difftime(end, start) * 1000.0;
		}
		
		print_out ( "short_int" , loop_count);
		print_break();
		reset_values();
		
		/////////// Long Integer //////////
		while (timer < 5)
		{
			start = GetTickCount(); //time_t start = time(0);
			
			while (ops<loop)
			{
				temp_add = calc_add (temp_add, long_int) ;
				temp_sub = calc_sub (temp_sub, long_int) ;
				temp_mul = calc_mul (temp_mul, long_int) ;
				temp_div = calc_div (temp_div, long_int) ;
				ops = ops +1;
			}
			loop_count = loop_count + 1;
			end = GetTickCount(); //time_t end = time(0);
			timer = difftime(end, start) * 1000.0;
		}
		print_out ( "long_int" , loop_count);
		print_break();
		reset_values();
		
		/////////// single_precision_float //////////
		while (timer < 5)
		{
			start = GetTickCount(); //time_t start = time(0);
			
			while (ops<loop)
			{
				temp_add = calc_add (temp_add, single_precision_float) ;
				temp_sub = calc_sub (temp_sub, single_precision_float) ;
				temp_mul = calc_mul (temp_mul, single_precision_float) ;
				temp_div = calc_div (temp_div, single_precision_float) ;
				ops = ops +1;
			}
			loop_count = loop_count + 1;
			end = GetTickCount(); //time_t end = time(0);
			timer = difftime(end, start) * 1000.0;
		}
		print_out ( "single_precision_float" , loop_count);
		print_break();
		reset_values();
		
				/////////// double_precision_float //////////
		while (timer < 5)
		{
			start = GetTickCount(); //time_t start = time(0);
			
			while (ops<loop)
			{
				temp_add = calc_add (temp_add, double_precision_float) ;
				temp_sub = calc_sub (temp_sub, double_precision_float) ;
				temp_mul = calc_mul (temp_mul, double_precision_float) ;
				temp_div = calc_div (temp_div, double_precision_float) ;
				ops = ops +1;
			}
			loop_count = loop_count + 1;
			end = GetTickCount(); //time_t end = time(0);
			timer = difftime(end, start) * 1000.0;
		}
		print_out ( "double_precision_float" , loop_count);
		print_break();
		reset_values();
		
		state = END;
	}
	
	if (state == END)
	{
		char answer ;
		print_break()
		cout << '\n\n\n \t\tCalculations complete';
		cout << '\n\n\n Calculations Again Y/N ? ';
		cin >> answer;
		
		if (answer = "Y") state = Add_Sub;
		else cout << '\n\n\n \t\t Good Bye' break;
	}
}

////////////////////////////////////////////////////////////////////
////////////////// 		Creating Functions		 //////////////////

////////////////////////////////////////////////////////
/////////////	 		Print Functs 		////////////
////////////////////////////////////////////////////////
void print_break()
{
	cout << '\n- - - - - - - - - - - - - - - - - - - - -  ';
} 
void print_title(int var_type)
{
	cout << '\n|' << setw(10) << var_type << ' | ' setw(10) << 'Result |' << endl;
}
void print_out(char var_type, int value)
{
	cout << '\n|' << setw(10) << var_type << ' | ' setw(10) << value << ' |' << endl;
}

////////////////////////////////////////////////////////
/////////////		Calculation Functs 		////////////
////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////
/////////////		Declaring Funct 		////////////
////////////////////////////////////////////////////////
int reset_values ()
{
	temp_add   = 0;
	temp_sub   = 0;
	temp_mul   = 0;
	temp_div   = 0;
	loop_count = 0;
	ops = 0;
	timer= 0;
}