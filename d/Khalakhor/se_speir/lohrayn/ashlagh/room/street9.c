// street through the village
#include "defs.h"
inherit STREET;
 
public void reset_room() { make_guards(); }

public int* query_local_coords() { return ({1,5}); }
 
create_khalakhor_room()
{
   extra = "There is an arch which marks an entrance to the village "+
           "to the west, though great wooden gates mounted in the "+
           "arch are closed. A banner flutters from atop the arch.";
   create_street();
   add_item(({"arch","entrance"}),
      "A high arch in the stone wall which surrounds the village "+
      "provides an entrance to the settlement to the west, though "+
      "the gates mounted in it are closed. "+
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
   add_item(({"gates","gate"}),
      "The gates are mounted on great hinges into the arch and are "+
      "made of very thick beams of wood. They seem to be closed for "+
      "protection.\n");
   add_cmd_item(({"gates","gate"}),({"open","unlock"}),
      "The gates are locked and can not be unlocked or opened.\n");
   add_cmd_item(({"gates","gate"}),({"close","lock"}),
      "The gates are already closed and locked.\n");
 
   add_exit("street8","east");
   reset_room();
}
