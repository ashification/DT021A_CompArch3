///////////////////////////////////////////////////////////////////////////////
// Aisling Lee		C12358536		DT021A Year 4	Computer Architecture 3  //
//	Due to time constrains I recieved help from Evin Hughes		     //
///////////////////////////////////////////////////////////////////////////////

//////////////////Library Declarations///////////////////////////////////////
#include <stdio.h>
#include <iomanip>
#include <bitset>  //bitset - print all bits including 0's
#include <string>  //string - data from input file is read in as string
#include <fstream> //fstream - read in external text file
#include <sstream> //sstream - convert string data to hex format
#include <iostream>//iostream - used for printing results
using namespace std;


//////////////////////////////////////////////////////////////////////////////
////////////////// Declaring variables //////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

	ifstream cpu_address("address.txt");	//Open and read in addresses from "address.txt" file, and attach to cpu_address	
	unsigned char word;
	string text_line_in;
	unsigned short memoryaddr = 0;
	int memoryline = 0;
	int hit_way0 = 0;				
	int hit_way1 = 0;
	int miss_way0 = 0;				
	int miss_way1 = 0;
	int set_no;
	int tag_addr;

//////////////////////////////////////////////////////////////////////////////
//////////////////Structure Declarations//////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
struct cache_data
{	
	// Structure representing a single line in the cache
	//unsigned char higherCPUAddr;	// Higher CPU Address stored in cache
	bool validflag;					// Valid Flag variabe
	bool lruflag;					// Least Recently Used Flag  variabe
	char mem_loc [4];					// array of four 1 byte memory locations
	unsigned char tag;				// Stores tag 
	unsigned char set;				// Stores set
	
}
way0[64], way1[64];				// Create two cache entry structures



struct dram_block 
{
	unsigned short dramaddr; //2 byte short for storing address
	unsigned char dramdata; //1 byte char for storing data @ above address
} dram_memory[1024]; //1Kb of DRAM memory declared

//////////////////////////////////////////////////////////////////////////////
//////////////////Function Declarations///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void clear_cache(cache_data way0[],cache_data way1[])
{
	// Initilise Valid and LRU Flags
	while (int counter = 0; counter<64; counter++) // declare and increment counter value and loop for all 64 elements (64 possible sets)
	{
		way0[i].valid_flag = 0; // reset valid_flag for way 0
		way1[i].valid_flag = 0; // reset valid_flag for way 1

		way0[i].lru_flag = 0; // reset lru_flag for way 0
		way1[i].lru_flag = 0; // reset lru_flag for way 1	
	}
}

void print_setup ()
{
	cout << " \t\tAisling Lee\n";
	cout << " \t\tC12358536, DT021A Year 4\n";
	cout << " \t\tComputer Architecture 3: Formal element\n";
	cout << " \t\t2-Way Set Associative Cache\n";
	cout << "--------------------------------------------------------------------|\n";
	cout << "| Address | Status | Location (Set #) | Data |\n";
	cout << "|----------------|----------------|----------------|----------------|\n";
}

void print_info ()
{
	if (print_hit == 1)
	{
		cout << "|"<< addr << "|  HIT	|"<< location <<"|"<< data <<"|\n"<<;
		cout << "|----------------|----------------|----------------|----------------|\n";
	}
	else if (print_miss ==1)
	{
		cout << "|"<< addr << "|  MISS	|"<< location <<"|"<< data <<"|\n"<<;
		cout << "|----------------|----------------|----------------|----------------|\n";
	}

}

void print_end ()
{
	cout << "|--------------------------------------------------------------------|\n";
	
	cout << " Results of Cach checking" << endl;
	cout << " Hit Count for Way 0: " << dec << hit_way0 << endl;
	cout << " Hit Count for Way 1: " << dec << hit_way1 << endl;
	cout << "Miss Count for Way 0: " << dec << miss_way0 << endl;
	cout << "Miss Count for Way 1: " << dec << miss_way1 << endl;	
}

int address_setup (string, string, int, int)
{
		istringstream(text_line_in) >> hex >> cpu_address; // convert the incoming string line (extracted from the text file) into a hex value and store it in cpu_address variable
		tag_addr = cpu_address & 0xff00;		// make all bits zero
		tag_addr >>= 8;						//bitshift tag 8 bits 
		set_no = cpu_address & 0x00ff;  // make all bits zero
		set_no >>= 2;					//bitshift setno 2 bit

		return set_no, tag_addr;
}

int dram_setup()
{
	//Populating DRAM with random data spanning from address 0x8000 - 0x8400
	while (int loop_counter = 0; loop_counter < 1024; loop_counter++) 
	{
		dram_memory[loop_counter].dramaddr = 0x8000 + loop_counter;
		dram_memory[loop_counter].dramdata = rand() % 255;
	}
}

void cache_hit_check ()
{
	if ((way0[set_no].tag == tag_addr) && (way0[set_no].validflag = 1))
	{
		cout << "| " << hex << cpu_address << " | Hit " << "| Way 0  "<<dec << set_no; 
		cout << "|     "<< hex<<tag_addr<<" |\n"<< endl;
		
		//Increment hit counter & swap LRU flags
		hit_way0++;
		way0[set_no].lruflag = 0;
		way1[set_no].lruflag = 1;
	}

	else if ((way1[set_no].tag == tag_addr) && (way1[set_no].validflag = 1))
	{
		cout << "| " << hex << cpu_address << " | Hit " << "| Way 1  "<<dec << set_no;
		cout << "|     "<< hex<<tag_addr<<" |\n"<< endl;
		
		//Increment hit counter & swap LRU flags
		hit_way1++;
		way0[set_no].lruflag = 1;
		way1[set_no].lruflag = 0;
	}
	
}

void cache_miss()
{
	//If way0 is the least recently used path
	if (way0[setno].lruflag == 1) 
	{
		cout << "| " << hex << cpu_address << " | MISS " << "| Way 0  "<<dec << set_no" |     ";
		way0[setno].tag = tag_addr; //update the tag to a new value
		
				
		//Step through DRAM blocks until requested cache address is found
		while (memoryaddr != cpuaddr) 
		{
			memoryaddr = memoryBlock[memoryline].dramaddr;
			memoryline++;
		}
				
		//Read data @ cache boundary address & next 3 data lines into cache line
		while (int loop_counter = 0; loop_counter < 4; loop_counter++) 
		{
			way0[setno].data[i] = memoryBlock[memoryline + i].dramdata;
			cout << hex << way0[setno].data[i] << " |\n"<< endl;

		}
				
		//Increment miss counter & swap LRU flags
		miss_way0++;
		way0[setno].lruflag = 0;
		way1[setno].lruflag = 1;
	}
			
	else if (way1[setno].lruflag == 1) 
	{
		cout << "| " << hex << cpu_address << " | MISS " << "| Way 1  "<<dec << set_no" |     ";
		way0[setno].tag = tag_addr; //update the tag to a new value
		
				
		//Step through DRAM blocks until requested cache address is found
		while (memoryaddr != cpuaddr) 
		{
			memoryaddr = memoryBlock[memoryline].dramaddr;
			memoryline++;
		}
				
		//Read data @ cache boundary address & next 3 data lines into cache line
		while (int loop_counter = 0; loop_counter < 4; loop_counter++) 
		{
			way0[setno].data[i] = memoryBlock[memoryline + i].dramdata;
			cout << hex << way0[setno].data[i] << " |\n"<< endl;

		}
				
		//Increment miss counter & swap LRU flags
		miss_way0++;
		way0[setno].lruflag = 1;
		way1[setno].lruflag = 0;
	}
}

//////////////////Main////////////////////////////////////////////////////
int main()
{
	

	//  Set up	//
	clear_cache(way0, way1);				// Initilises Cache Variables to zero (Except the LRU Flags on way1[] is set to 1)
	dram_setup ();
	print_setup ();							// Print out soln details and set up table

	while(getline(cpu_address, text_line_in)) 
	{
		address_setup(cpu_address, text_line_in,tag,set_no);
		if ((way0[setno].tag == tag_addr) || (way0[setno].tag == tag_addr)) cache_hit_check();
		else cache_miss();

	}
		
	system ("pause");	//Pauses the console
	return 0;
}