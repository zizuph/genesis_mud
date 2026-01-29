// street through the village
#include "defs.h"
inherit STREET;
 
public int* query_local_coords() { return ({5,4}); }
 
create_khalakhor_room()
{
   extra = "The street runs along the north side of the commons to "+
           "the east and west, while there is a small courtyard to "+
           "the north.";
   create_common();
   add_item("courtyard",
      "It is a small grassy courtyard just to the north with three "+
      "homes or buildings situated around it.\n");
   add_exit("courtk",  "north");
   add_exit("street6n","west");
   add_exit("street4n", "east");
}
