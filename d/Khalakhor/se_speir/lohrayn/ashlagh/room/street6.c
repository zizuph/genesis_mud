// street through the village
#include "defs.h"
inherit STREET;
 
public int* query_local_coords() { return ({4,5}); }
 
create_khalakhor_room()
{
   extra = "The street goes around the commons to the north and south "+
           "and leads futher through the village to the west.";
   create_common();
   add_exit("street6n","north");
   add_exit("street6s","south");
   add_exit("street7", "west");
}
