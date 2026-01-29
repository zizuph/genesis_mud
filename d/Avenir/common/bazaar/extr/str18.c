// Bazaar Street19 (/d/Avenir/common/bazaar/extr/str19.c)
// creator(s):   Triana 1994
// last update:  Tepisch Aug 94, Ilyian May 95
// purpose:
//
// note:
// bug(s):
// to-do:
 
 
inherit "/d/Avenir/common/bazaar/extr/std_center.c";
 
#include "/d/Avenir/common/bazaar/bazaar.h"
 

void
create_room()
{
   AE(EXTR + "str17","west", 0);
   AE(EXTR + "str12", "north", 0);
   AE(EXTR + "str19", "east", 0);
   AE(INTR + "shop", "south", 0);
 
   SHORT("Southern end of Bazaar, near a shop");
   make_the_room("\n   South is what seems to be a small shop, and east, "
       +"west, and north lie the rest of the bazaar.\n");
 
}
 
