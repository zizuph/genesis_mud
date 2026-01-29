#include "defs.h"
inherit PROAD;
 
public int* query_local_coords() { return ({14,7}); }
 
public void create_khalakhor_room()
{
   extra="You hear the sqawking of sea gulls flying overhead. ";
   create_proad();
   add_item(({"seagull","sea gull","seagulls","sea gulls","gull","gulls"}),
      "They are common sea gulls, flying in circles over the shore "+
      "in search of food, sqawking noisily.\n");
   add_exit("proad4","west");
   add_exit("proad6","northeast");
}
