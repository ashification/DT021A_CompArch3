// Formal Element.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Cache.h"
ifstream addr ("ADDR.txt");	// Opens The address file ADDR.txt

//////////////////Structure Declarations////////////////////////////////////////////////////

struct cacheEntry{	
	// Structure representing a single line in the cache
	unsigned char higherCAddr;	// Higher CPU Address stored in cache
	bool validFlag;		// Valid Flag
	bool modifiedFlag;	// Modified Flag
	bool lruFlag;		// Least Recently Used Flag 
	unsigned char lineData[4];	// array of four 1 byte memory locations
	};

//////////////////Function Declarations///////////////////////////////////////////

void resetCache(cacheEntry[], cacheEntry[]);
void splitAddress(unsigned char *, unsigned char *, unsigned char *, char16_t *, string *);
int checkCache(unsigned char, unsigned char, cacheEntry[], cacheEntry[]);
void writeToCacheTag(unsigned char, unsigned char, cacheEntry[], cacheEntry[]);
void writeToCacheData(unsigned char, cacheEntry[], char16_t);
void getCacheData(unsigned char, cacheEntry[], unsigned char);

//////////////////Main////////////////////////////////////////////////////

int _tmain(int argc, _TCHAR* argv[]){
	struct cacheEntry way0[64], way1[64]; // Create two cache entry structures
	string addrline;				// Stores CPU Address from ADDR file
	unsigned char tag;				// Stores tag (addrline * 1111 1111 0000 0000)
	unsigned char set;				// Stores set (addrline * 0000 0000 1111 1100)
	unsigned char word;				// Stores word (addrline * 0000 0000 0000 0011)
	char16_t tagAndSet;				// Stores tag and set (addrline * 1111 1111 1111 1100)
	int hit;					// Stores return from checkCache function

	cout<<"This program simulates a two way set associative cache with single byte words."<<endl<<endl;
	resetCache(way0, way1);			// Initilises Cache Variables to zero (Except the LRU Flags on way1[] is set to 1)
	
	for(int i=0;i<16;i++){
		splitAddress(&set, &tag, &word, &tagAndSet, &addrline); //Splits the address into its sections
		cout<<"Address: "<<addrline<<endl;	// Prints Address from ADDR.txt

		hit = checkCache(set, tag, way0, way1); // Checks the cache for a hit or a miss
		
		if(hit == 0){
			cout<<"Not in cache"<<endl<<endl;
			writeToCacheTag(set, tag, way0, way1);	// Writes missed address to cache tag
			
			if(way0[set].lruFlag == 0)
				writeToCacheData(set, way0, tagAndSet);	// Writes Data from DRAM.txt to Cache Data

			else
				writeToCacheData(set, way1, tagAndSet);	// Writes Data from DRAM.txt to Cache Data
		}
		
		else{
			cout<<"In Cache"<<endl;
			
			if(way0[set].lruFlag == 0)
				getCacheData(set, way0, word);	// Returns Selected data from Cache Data
	
			else
				getCacheData(set, way1, word);	// Returns Selected data from Cache Data
		}
	}
	addr.close();	//Closes the ADDR.txt file
	system ("pause");	//Pauses the console
	return 0;
}



//////////////////Functions////////////////////////////////////////////////////

void resetCache(cacheEntry way0[],cacheEntry way1[]){
	// Initilise Flags
	for(int i=0; i<64;i++){
		way0[i].higherCAddr = 'x';
		way0[i].validFlag = 0;
		way0[i].modifiedFlag = 0;
		way0[i].lruFlag = 0;
		way1[i].higherCAddr = 'x';
		way1[i].validFlag = 0;
		way1[i].modifiedFlag = 0;
		way1[i].lruFlag = 1;
	}
}

void splitAddress(unsigned char *set, unsigned char *tag, unsigned char *word, char16_t *tagAndSet, string *addrline){
	// Splits address from ADDR.txt into set, tag, word and tag and set sections
	if (addr.is_open()){
		getline (addr, *addrline);	// stores address from addr into addrline

		*set = stoi(*addrline, nullptr, 16) >>2 & (0x003F);	// Stores set from (addrline * 0000 0000 1111 1100)
		*tag = stoi(*addrline, nullptr, 16) >>8;			// Stores tag (addrline * 1111 1111 0000 0000)
		*word = stoi(*addrline, nullptr, 16) & 0x003;		// Stores word (addrline * 0000 0000 0000 0011)
		*tagAndSet = stoi(*addrline, nullptr, 16)>>2;		// stores tag and set (addrline 1111 1111 1111 1100)
	}

	else 
		cout << "file not open";		//Error message if file not open
}

int checkCache(unsigned char set, unsigned char tag, cacheEntry way0[], cacheEntry way1[]){
	// Checks tag address stored in the cache tags against current tag from ADDR.txt for a hit or miss
	if(tag == way0[set].higherCAddr && way0[set].validFlag == 1){
		way1[set].lruFlag = 1;
		way0[set].lruFlag = 0;
		return 1;
	}

	else if (tag == way1[set].higherCAddr && way1[set].validFlag == 1){
		way0[set].lruFlag = 1;
		way1[set].lruFlag = 0;
		return 1;
	}

	else
		return 0;
}

void writeToCacheTag(unsigned char set, unsigned char tag, cacheEntry way0[], cacheEntry way1[]){
	// Writes tag address from ADDR.txt to the cache tag
	if(way0[set].lruFlag == 1){
	way0[set].higherCAddr = tag;	// Set Upper Address in cache tag
	way0[set].validFlag = 1;	// Validate address in cache tag for use
	way0[set].lruFlag = 0;	// Set way0 address to be most recently used
	way1[set].lruFlag = 1; // Set way1 address to be least recently used
	}

	else if(way1[set].lruFlag == 1){
	way1[set].higherCAddr = tag; // Set Upper Address in cache tag
	way1[set].validFlag = 1; // Validate address in cache tag for use
	way1[set].lruFlag = 0;	// Set way1 address to be most recently used
	way0[set].lruFlag = 1;	// Set way0 address to be least recently used
	}
}

void writeToCacheData(unsigned char set, cacheEntry way[], char16_t tagAndSet){
	// Writes data from DRAM.txt to cache data
	ifstream dram ("DRAM.txt");	// Opens DRAM File
	string buffer;	//stores data from DRAM.txt
	
	for (int x =0; x<=tagAndSet;x++)	// Loops through DRAM to find Data
		getline(dram,buffer);			// Stores data from dram into buffer
	
	way[set].lineData[0] = stol(buffer, nullptr, 16)>>24;		 // Stores 8 bit word in cache line (11111111 00000000 00000000 00000000)
	way[set].lineData[1] = stol(buffer, nullptr, 16)>>16 & 0xFF; // (00000000 11111111 00000000 00000000)
	way[set].lineData[2] = stol(buffer, nullptr, 16)>>8 & 0xFF;	 // (00000000 00000000 11111111 00000000)
	way[set].lineData[3] = stol(buffer, nullptr, 16) & 0xFF;	 // (00000000 00000000 00000000 11111111)
	dram.close();	// Closes DRAM.txt file
}

void getCacheData(unsigned char set, cacheEntry way[], unsigned char word){
	// Prints Selected data byte from cache data
	cout<<"Data sent to CPU: "<<hex<<(int)way[set].lineData[word]<<endl<<endl;
}