struct cache line
{
  unsigned chr tag; 
  bool valuesflag;
  bool LRUflag;
  char data [4];
}

way0 [64], way1[64];
unsigned short cpuaddr;

main 
{
  for (int c = 0;  c< 64; L++)
 {
   way 0 [c].valueflag =0;
   way 1 [c].valueflag =0;

   way 0 [c].LRUflag =0;
   way 1 [c].LRUflag =0;
  }
 
  txtfileentry -> cpuaddr
  setn = (cpuaddr & 0x00ff)>>2;
  uppraddr (...&0xff00)>>8;

    if ((way0[setno].tag == uppraddr)&&(way0[setno].valueflag =1))
      {
         //hit on way0
         hit count way 0 ++ ; 
         LRU for way 0 =0; 
         LRU for way 1 = 1;
       }

   else if ((way1[setno].tag == uppraddr)&&(way1[setno].valueflag =1))
     { 
           //hit on way1, 
           hit count way 1 ++ ; 
           LRU for way 0 =1; 
           LRU for way 1 = 0
      }

     else if 
        { 
           //misc  
             check lru = 1; 
             -> way; 
             replace tag with cpuaddr;  
             adjust LRU; 
             update flags;
             update data;
             misscounter ++;
         }
}