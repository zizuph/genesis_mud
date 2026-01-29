// street through the village
#include "defs.h"
inherit STREET;
 
public int* query_local_coords() { return ({2,5}); }
 
create_khalakhor_room()
{
   extra = "There are two courtyards just off the street here "+
           "to the north and south, each with three homes or buildings "+
           "situated around them.";
   create_street();
   add_item(({"courtyard","courtyards"}),
      "There are two small grassy courtyards just off the street "+
      "here, one to the north and the other to the south. Three "+
      "of the pastel colored homes or buildings is situated "+
      "around each with entrances leading into the yard.\n");
   add_exit("court4","north");
   add_exit("court3","south");
   add_exit("street9","west");
   add_exit("street7","east");
}
