// street through the village
#include "defs.h"
inherit STREET;
 
public int* query_local_coords() { return ({2,6}); }
 
create_khalakhor_room()
{
   extra="The buildings around this court look somewhat commercial, "+
         "each with a sign hanging out from a pole over their entrances.";
   add_item(({"signs","sign","pole","poles"}),
      "There is a sign hangout out over the entrance of each building "+
      "from a pole. Perhaps you could read them.\n");
   add_cmd_item(({"signs","sign"}),"read",
      "Which one? the west, east or south?\n");
   add_cmd_item("east sign", "read","LYRR'S SHOPPE\n");
   add_cmd_item("west sign","read","For Sale\n");
   add_cmd_item("south sign","read","THE TAIGH LEANN\n");
   create_court("north");
   add_exit("street8", "north");
   add_exit("pub",     "south");
   add_exit("shop",    "east");
   add_exit("post",     "west");
}
