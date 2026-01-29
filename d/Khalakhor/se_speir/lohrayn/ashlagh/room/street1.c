// street through the village
#include "defs.h"
inherit STREET;
 
public void reset_room() { make_guards(); }
 
public int* query_local_coords() { return ({9,5}); }
 
create_khalakhor_room()
{
   extra = "The arch which marks the entrance to the village is "+
           "just to the east, a banner flying atop it.\n";
   create_street();
   add_item(({"arch","entrance"}),
      "A high arch in the stone wall which surrounds the village "+
      "provides an entrance to the settlement to the east. "+
      "An inscription is sculpted into the smooth stones which "+
      "have been set along the top of the arch, while a banner "+
      "flies from a pole on top of it.\n");
   add_item("inscription","It is written along the top of the arch.\n");
   add_cmd_item(({"inscription","arch"}),"read",
      "BAILE ASHLAGH\n");
   add_item(({"banner","pole"}),
      "A large banner hangs from a pole atop the arch over the "+
      "entrance to the village, which seems to be a fleet of nine "+
      "sailing ships on a purple background.\n");
   add_exit("street2","west");
   add_exit("proad1", "east", "@@go_arch");
   reset_room();
}
 
int go_arch()
{
   write("You pass beneath the arch out of the village.\n");
   return 0;
}
