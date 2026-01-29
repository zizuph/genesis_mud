#include "defs.h"
inherit PROAD;
 
public int* query_local_coords() { return ({10,5}); }
 
public void create_khalakhor_room()
{
   extra="A high arch in the wall of the village marks its entrance "+
         "to the west.";
   create_proad();
   add_item(({"arch","entrance"}),
      "A high arch in the stone wall which surrounds the village "+
      "provides an entrance to the settlement to the west. "+
      "An inscription is sculpted into the smooth stones which "+
      "have been set along the top of the arch, while a banner "+
      "hangs from a pole on top of it.\n");
   add_item("inscription","It is written along the top of the arch.\n");
   add_cmd_item(({"inscription","arch"}),"read",
      "BAILE ASHLAGH\n");
   add_item(({"banner","pole"}),
      "A large banner hangs from a pole atop the arch over the "+
      "entrance to the village, which seems to be a fleet of nine "+
      "sailing ships on a purple background.\n");
   add_exit("street1","west","@@go_arch");
   add_exit("proad2","southeast");
}

int go_arch()
{
   write("You pass beneath the arch into the village.\n");
   return 0;
}
