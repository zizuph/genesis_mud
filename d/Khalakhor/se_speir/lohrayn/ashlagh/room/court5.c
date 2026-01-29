// street through the village
#include "defs.h"
inherit STREET;
 
public int* query_local_coords() { return ({7,4}); }
 
create_khalakhor_room()
{
   extra="The building to the north is rather odd, as it is made of stone.";
   create_court("south");
   add_exit("home1",  "north");
   add_exit("street2","south");
   add_exit("home9",  "east");
   add_exit("home8", "west");
   add_item(({"stone building","building","north building"}),
      "The building to the north looks very out of place in the village, "+
      "as it is made of stone instead of wood like all the others. Its "+
      "walls seems to sag a bit, though its thatch roof looks fairly "+
      "new.\n");
}
