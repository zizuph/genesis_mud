// street through the village
#include "defs.h"
inherit STREET;
 
public int* query_local_coords() { return ({6,6}); }
 
create_khalakhor_room()
{
   extra = "The street goes around the commons to the north and west "+
           "while there is an entrance to the commons green to the "+
           "northwest.";
   create_common();
   add_exit("street4",  "north");
   add_exit("green",    "northwest");
   add_exit("street5s", "west");
}
