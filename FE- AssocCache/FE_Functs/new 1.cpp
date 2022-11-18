///////////////////////////////////////////////////////////////////////////////
//                        Aisling Lee        C12358536                             //
//                                 DT021A Year 4                                  //
//                          Computer Architecture 3                             //
//                          Last modified 24/11/2017                             //
///////////////////////////////////////////////////////////////////////////////

//////////////////Library Declarations///////////////////////////////////////
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include <tchar.h>
#include <windows.h>
#include <Winbase.h>
#include <bitset>  //bitset - print all bits including 0's
#include <string>  //string - data from input file is read in as string
#include <fstream> //fstream - read in external text file
#include <sstream> //sstream - convert string data to hex format
#include <iostream>//iostream - used for printing results
using namespace std;



//////////////////////////////////////////////////////////////////////////////
//////////////////Structure Declarations//////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
struct cache_data
{    
    // Structure representing a single line in the cache
    //unsigned char higherCPUAddr;    // Higher CPU Address stored in cache
    bool validflag;                    // Valid Flag variabe
    bool lruflag;                    // Least Recently Used Flag  variabe
    char mem_loc [4];                // array of four 1 byte memory locations
    unsigned char tag;                // Stores tag 
    unsigned char set;                // Stores set
    
}
way0[64], way1[64];                // Create two cache entry structures



struct dram_block 
{
    unsigned short dramaddr; //2 byte short for storing address
    unsigned char dramdata; //1 byte char for storing data @ above address
} dram_memory[1024]; //1Kb of DRAM memory declared

//////////////////////////////////////////////////////////////////////////////
//////////////////Function Declarations///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

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



//////////////////Main////////////////////////////////////////////////////
int main()
{
    
    
    //  Set up    //
    unsigned short cpu_address;
    string text_line_in;
    unsigned short memoryaddr = 0;
    int memoryline = 0;
    int hit_way0 = 0;                
    int hit_way1 = 0;
    int miss_way0 = 0;                
    int miss_way1 = 0;
    int set_no;
    int tag_addr;

	int counter = 0; 
	// Initilises Cache Variables to zero (Except the LRU Flags on way1[] is set to 1)
    while (counter++<64) // declare and increment counter value and loop for all 64 elements (64 possible sets)
    {
        way0[counter].validflag = 0; // reset valid_flag for way 0
        way1[counter].validflag = 0; // reset valid_flag for way 1

        way0[counter].lruflag = 0; // reset lru_flag for way 0
        way1[counter].lruflag = 0; // reset lru_flag for way 1
    }
 
    print_setup ();                            // Print out soln details and set up table
	
	//Populating DRAM with random data spanning from address 0x8000 - 0x8400
	int loop_counter = 0; 
    while (loop_counter++ < 1024 ) 
    {
        dram_memory[loop_counter].dramaddr = 0x8000 + loop_counter;
        dram_memory[loop_counter].dramdata = rand() % 255;
    }
    
	
    ifstream cpu_address_list("address.txt");    //Open and read in addresses from "address.txt" file, and attach to cpu_address    
    while (getline(cpu_address_list, text_line_in)) 
    {
        //cout << " \n I am in while loop\n";
        istringstream(text_line_in) >> hex >> cpu_address; // convert the incoming string line (extracted from the text file) into a hex value and store it in cpu_address variable
        tag_addr = (cpu_address & 0xff00);        // make all bits zero
        tag_addr >>= 8;                        //bitshift tag 8 bits 
        set_no = cpu_address & 0x00ff;  // make all bits zero
        set_no >>= 2;                    //bitshift setno 2 bit
        
        cout << " \n I am in cache hit check\n";
        if ((way0[set_no].tag == tag_addr) && (way0[set_no].validflag = 1))
        {
            cout << " \n I am in cache hit check way0\n";
            cout << "| " << hex << cpu_address << " | Hit " << "| Way 0  "<<dec << set_no << "|     "<< hex<<tag_addr<<" |\n"<< endl;
        
            //Increment hit counter & swap LRU flags
            hit_way0++;
            way0[set_no].lruflag = 0;
            way1[set_no].lruflag = 1;
        }

        else if ((way1[set_no].tag == tag_addr) && (way1[set_no].validflag = 1))
        {
            cout << " \n I am in cache hit check way1\n";
            cout << "| " << hex << cpu_address << " | Hit " << "| Way 1  "<<dec << set_no << "|     "<< hex<<tag_addr<<" |\n"<< endl;
        
            //Increment hit counter & swap LRU flags
            hit_way1++;
            way0[set_no].lruflag = 1;
            way1[set_no].lruflag = 0;
        }
        

        else 
        {
            //If way0 is the least recently used path
            if (way0[set_no].lruflag == 1) 
            {
                cout << "| " << hex << cpu_address << " | MISS " << "| Way 0  "<<dec << set_no <<" |     ";
                way0[set_no].tag = tag_addr; //update the tag to a new value
        
                
                //Step through DRAM blocks until requested cache address is found
                while (memoryaddr =! cpu_address) 
                {
                    memoryaddr = dram_memory[memoryline].dramaddr;
                    memoryline++;
                }
                
                //Read data @ cache boundary address & next 3 data lines into cache line
                int loop_counter = 0;
                while (loop_counter++ < 4) 
                {
                    way0[set_no].mem_loc[loop_counter] = dram_memory[memoryline + loop_counter].dramdata;
                    cout << hex << way0[set_no].mem_loc[loop_counter] << " |\n"<< endl;

                }
                
                //Increment miss counter & swap LRU flags
                miss_way0++;
                way0[set_no].lruflag = 0;
                way1[set_no].lruflag = 1;
            }
            
            else if (way1[set_no].lruflag == 1) 
            {
                cout << "| " << hex << cpu_address << " | MISS " << "| Way 1  "<<dec << set_no <<" |     ";
                way0[set_no].tag = tag_addr; //update the tag to a new value
        
                
                //Step through DRAM blocks until requested cache address is found
                while (memoryaddr =! cpu_address) 
                {
                    memoryaddr = dram_memory[memoryline].dramaddr;
                    memoryline++;
                }
                
                //Read data @ cache boundary address & next 3 data lines into cache line
                int loop_counter = 0;
                while ( loop_counter++ < 4) 
                {
                    way0[set_no].mem_loc[loop_counter] = dram_memory[memoryline + loop_counter].dramdata;
                    cout << hex << way0[set_no].mem_loc[loop_counter++] << " |\n"<< endl;

                }
                
                //Increment miss counter & swap LRU flags
                miss_way0++;
                way0[set_no].lruflag = 1;
                way1[set_no].lruflag = 0;
            }
        }

        
    }
    
    //print_end();

    cout << "|--------------------------------------------------------------------|\n";
    
    cout << " Results of Cache Analysis" << endl;
    cout << " Hit Count: Way 0: " << dec << hit_way0 <<"Way 1: " << dec << hit_way1 << endl;
    cout << " Miss Count: Way 0: " << dec << miss_way0 << " Way 1: " << dec << miss_way1 << endl;    

    system ("pause");    //Pauses the console
    return 0;
}