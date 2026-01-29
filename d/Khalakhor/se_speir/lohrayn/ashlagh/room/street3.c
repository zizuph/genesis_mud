// street through the village
#include "defs.h"
inherit STREET;
 
public int* query_local_coords() { return ({7,5}); }

create_khalakhor_room()
{
   extra = "The town square, called the village commons, is to the "+
           "west.";
   create_street();
   add_item(({"square","town square","commons","village commons"}),
      "It is the commons in the center of the village, just to "+
      "the west.\n");
   add_exit("street4","west");
   add_exit("street2","east");
}
