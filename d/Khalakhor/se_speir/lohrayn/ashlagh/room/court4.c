// street through the village
#include "defs.h"
inherit STREET;
 
public int* query_local_coords() { return ({2,4}); }
 
create_khalakhor_room()
{
   create_court("south");
   add_exit("home6",  "north");
   add_exit("street8","south");
   add_exit("home7","east");
   add_exit("home5",  "west");
}
