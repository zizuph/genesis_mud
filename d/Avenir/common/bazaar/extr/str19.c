
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

object slave1, slave2, slave3;
object maya;

reset_room()
{

   if(!maya)
   {
   maya = clone_object(BAZAAR+"NPCS/maya");
    maya->arm_me();
   maya->move(TO);
   }
  if (!slave1)
   {
      slave1 = clone_object(BAZAAR + "NPCS/wom1.c");
      slave1->arm_me();
      slave1->move_living("M", this_object());
    }

  if (!slave2)
   {
      slave2 = clone_object(BAZAAR + "NPCS/man1.c");
      slave2->arm_me();
      slave2->move_living("M", this_object());
    }

  if (!slave3)
   {
      slave3 = clone_object(BAZAAR + "NPCS/ch1.c");
      slave3->arm_me();
      slave3->move_living("M", this_object());
    }
}


void
create_room()
{
   AE(EXTR + "centr", "north", 0);
   AE(EXTR + "str18", "west", 0);
   AE(EXTR + "str20", "east", 0);
   AE(EXTR + "str22", "south", 0);

   SHORT("Southern end of Bazaar");
   make_the_room("\n   To the south the cobblestone square gives " +
      "way to a gravel path. The heady aroma of fresh-baked " +
      "bread wafts from the building to the southeast.\n");

   reset_room();
}

