// street through the village
#include "defs.h"
inherit STREET;
 

public int* query_local_coords() { return ({5,6}); }
 
create_khalakhor_room()
{
   extra = "The street runs along the south side of the commons to "+
           "the east and west, while there is a small courtyard to "+
           "the south.";
   create_common();
   add_item("courtyard",
      "It is a small grassy courtyard just to the south with three "+
      "homes or buildings situated around it.\n");
   add_exit("court2",  "south");
   add_exit("street6s","west");
   add_exit("street4s", "east");
}
