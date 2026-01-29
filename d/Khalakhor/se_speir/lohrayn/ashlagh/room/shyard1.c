// yard of the house of the Solsheyderi
#include "defs.h"
inherit STREET;
 
public int* query_local_coords() { return ({6,4}); }
 
create_khalakhor_room()
{
   create_court();
   set_short("In a yard in a quaint village");
   set_long("You are standing in a yard in the village, just off the "+
            "street which is to the southwest. A very old-looking house "+
            "sits to the north, its most distinguishing and a bit "+
            "astonishing characteristic is that it is made of stone "+
            "and has a thatched roof, making it completely out of "+
            "character for the village. The walls of the house look "+
            "to be even older than those of the wall around the village.\n");
   add_item("house",
      "It is a very old stone house, its walls drooping a bit. It has "+
      "a thatched roof and looks very out of place in this village. "+
      "It must have been left standing for some reason by the "+
      "villagers. There is an entrance to it to the north, next to "+
      "which a sign is posted.\n");
   add_item("sign",
      "Carved of wood and inset with brass lettering, the sign in "+
      "front of the stone house looks very attractive. Perhaps you "+
      "can read it.\n");
   add_cmd_item("sign","read",
      "THE ANCIENT ABODE OF THE SOLSHEYDERI\n"+
      "     Tours Given Anytime - 1 sc     \n");
   add_item(({"courtyard","grass","yard"}),
      "It seems a little out of pattern with the rest of the greens "+
      "and courts of the rest of the village, but it is just as well "+
      "tended.\n");
   add_exit("street4n", "southwest");
   add_exit("shabode",  "north");
}
