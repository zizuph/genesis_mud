// street through the village
#include "defs.h"
inherit STREET;
 
public int* query_local_coords() { return ({7,6}); }
 
create_khalakhor_room()
{
   create_court("north");
   add_exit("street2","north");
   add_exit("home3",  "south");
   add_exit("home2",  "east");
   add_exit("home4",  "west");
}
