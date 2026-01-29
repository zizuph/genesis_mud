// street through the village
#include "defs.h"
inherit STREET;
 
public void reset_room() { make_guards(); }

public int* query_local_coords() { return ({4,6}); }
 
create_khalakhor_room()
{
   extra = "The street goes around the commons to the north and east "+
           "while there is an entrance to the commons green to the "+
           "northeast.";
   create_common();
   add_exit("street6",  "north");
   add_exit("green",    "northeast");
   add_exit("street5s", "east");
   reset_room();
}
