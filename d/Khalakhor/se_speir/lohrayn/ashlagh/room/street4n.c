// street through the village
#include "defs.h"
inherit STREET;
 
public void reset_room() { make_guards(); }

public int* query_local_coords() { return ({6,4}); }
 
create_khalakhor_room()
{
   create_common();
   add_exit("street5n", "west");
   add_exit("green",    "southwest");
   add_exit("street4",  "south");
   reset_room();
}
