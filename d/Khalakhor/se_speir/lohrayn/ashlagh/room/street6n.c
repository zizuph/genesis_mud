// street through the village
#include "defs.h"
inherit STREET;
 
public int* query_local_coords() { return ({4,4}); }
 
create_khalakhor_room()
{
   extra = "The street goes around the commons to the south and east "+
           "while there is an entrance to the commons green to the "+
           "southeast.";
   create_common();
   add_exit("street6",  "south");
   add_exit("green",    "southeast");
   add_exit("street5n", "east");
}
