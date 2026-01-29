// street through the village
#include "defs.h"
inherit STREET;
 
public int* query_local_coords() { return ({5,7}); }
 
create_khalakhor_room()
{
   extra="The buildings around this court look rather official, each "+
         "with a sign next to its entrance. A banner hangs from "+
         "a pole over the entrance to the one to the south.";
   add_item(({"signs","sign"}),"Perhaps you could read it.\n");
   add_cmd_item(({"signs","sign"}),"read",
      "Which one? the west, east or south?\n");
   add_cmd_item("east sign", "read","BAILE ASHLAGH SCHOOL\n");
   add_cmd_item("west sign","read","FREICEADANAN DE BAILE ASHLAGH\n");
   add_cmd_item("south sign","read","BAILE ASHLAGH TOWN HALL\n");
   add_item(({"banner","pole"}),
      "A banner hangs from a pole over the entrance to the building "+
      "to the south. It bears a fleet of nine sailing ships on a "+
      "purple background.\n");
   create_court("north");
   add_exit("street5s","north");
   add_exit("townhall","south");
   add_exit("school",  "east");
   add_exit("guardhouse", "west");
}
