// street through the village
#include "defs.h"
inherit STREET;
 
public int* query_local_coords() { return ({3,5}); }
 
create_khalakhor_room()
{
   extra = "The village commons is just to the east.";
   create_street();
   add_item(({"square","town square","commons","village commons"}),
      "It is the commons in the center of the village, just to "+
      "the east.\n");
   add_exit("street8","west");
   add_exit("street6","east");
}
