// street through the village
#include "defs.h"
inherit STREET;
 
public int* query_local_coords() { return ({6,5}); }
 
create_khalakhor_room()
{
   extra = "The street goes around the commons to the north and south "+
           "and leads back to the entrance to the village to the east.";
   create_common();
   add_exit("street4n","north");
   add_exit("street4s","south");
   add_exit("street3", "east");
}
