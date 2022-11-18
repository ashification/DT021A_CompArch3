#include<iostream>
using namespace std;
int main()
{
	short test_var = 0x12ab;
	bool location = &test_var;
	bool read_out = (char*)location;
	
	if (read_out == 0x12)
	{
		cout << "big endian " ;
	}

	else
	{
		cout << "little endian " ;
	}
	
}

/* 
	int main()
	{
		short value;
		value = 0x12ab;
		char*ptr;
		ptr = (char*)&value
		
	
		if (ptr == 0x12)
		{
			cout << "big endian " ;
		}

		else
		{
			cout << "little endian " ;
		}
	
	}
*/