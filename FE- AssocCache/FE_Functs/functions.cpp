//////////////////Function Declarations///////////////////////////////////////////

void clear_cache(cache_data[], cache_data[]);
void splitAddress(unsigned char *, unsigned char *, unsigned char *, char16_t *, string *);
int checkCache(unsigned char, unsigned char, cache_data[], cache_data[]);
void writeToCacheTag(unsigned char, unsigned char, cache_data[], cache_data[]);
void writeToCacheData(unsigned char, cache_data[], char16_t);
void getCacheData(unsigned char, cache_data[], unsigned char);
void print_out_data(int)

//////////////////Functions////////////////////////////////////////////////////

void clear(cache_data way0[],cache_data way1[]){
	// Initilise Flags
	while (int counter = 0; counter<64; counter++) // for all 64 elements (64 possible sets)
	{
		way0[i].valid_flag = 0; // reset valid_flag for way 0
		way1[i].valid_flag = 0; // reset valid_flag for way 1

		way0[i].lru_flag = 1; // reset lru_flag for way 0
		way1[i].lru_flag = 1; // reset lru_flag for way 1	
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

int checkCache(unsigned char set, unsigned char tag, cache_data way0[], cache_data way1[])
{
	// Checks tag address stored in the cache tags against current tag from ADDR.txt for a hit or miss
	if(tag == way0[set].higherCPUAddr && way0[set].validflag == 1)
	{
		way1[set].lruflag = 1;
		way0[set].lruflag = 0;
		return 1;
	}

	else if (tag == way1[set].higherCPUAddr && way1[set].validflag == 1)
	{
		way0[set].lruflag = 1;
		way1[set].lruflag = 0;
		return 1;
	}

	else
		return 0;
}

void writeToCacheTag(unsigned char set, unsigned char tag, cache_data way0[], cache_data way1[])
{
	// Writes tag address from ADDR.txt to the cache tag
	if(way0[set].lruflag == 1)
	{
	way0[set].higherCPUAddr = tag;	// Set Upper Address in cache tag
	way0[set].validflag = 1;	// Validate address in cache tag for use
	way0[set].lruflag = 0;	// Set way0 address to be most recently used
	way1[set].lruflag = 1; // Set way1 address to be least recently used
	}

	else if(way1[set].lruflag == 1)
	{
	way1[set].higherCPUAddr = tag; // Set Upper Address in cache tag
	way1[set].validflag = 1; // Validate address in cache tag for use
	way1[set].lruflag = 0;	// Set way1 address to be most recently used
	way0[set].lruflag = 1;	// Set way0 address to be least recently used
	}
}

void writeToCacheData(unsigned char set, cache_data way[], char16_t tagAndSet)
{
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

void getCacheData(unsigned char set, cache_data way[], unsigned char word){
	// Prints Selected data byte from cache data
	cout<<"Data sent to CPU: "<<hex<<(int)way[set].lineData[word]<<endl<<endl;
}