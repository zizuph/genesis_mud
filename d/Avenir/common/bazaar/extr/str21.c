// Bazaar Street21 (/d/Avenir/common/bazaar/extr/str21.c)
// creator(s):   Triana 1994
// last update:  Tepisch Aug 94, Ilyian May 95
// purpose:
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/bazaar/extr/std_ctr2.c";

#include "/d/Avenir/common/bazaar/bazaar.h"

object guard1, guard2;

reset_room()
{
  if (!guard1)
   {
      guard1 = clone_object(BAZAAR + "NPCS/grd.c");
      guard1->arm_me();
      guard1->move_living("M", this_object());
    }
  if (!guard2)
   {
      guard2 = clone_object(BAZAAR + "NPCS/grd.c");
      guard2->arm_me();
      guard2->move_living("M", this_object());
    }
}

void
create_room()
{
   AE(EXTR + "str14", "north", 0);
   AE(INTR + "grdrm", "east", 0);
   AE(EXTR + "str20", "west", 0);
   AE(INTR + "lapidary", "south", 0);
   AE(INTR + "locket_shop", "tent", 0);

   SHORT("West of guardsmen's hut, outside the locket-smith tent, "+
       "north of gem shop");
   make_the_room("\n   The crowd seems to give the hut "+
      "to the east a wide berth. South is the lapidary shop "+
      "where gems are traded. A squarish grey tent sits here.\n");

   add_item(({"tent","square"}), "The tent is made from rough, "
     + "grey burlap, a flap of which is open into a well-lit "
     + "interior.  A sign stands outside the tent.\n");
   add_item(({"sign"}), "The sign reads: 'Lockets made and sold.'\n");
   add_cmd_item(({"sign"}), "read", "Lockets made and sold.\n");
   add_item("hut", "A mud-brick hut with a thatched roof that houses "+
     "off-duty guardsmen.\n");


   reset_room();
}

int
do_enter(string str)
{
   if (str=="tent" || str== "merchant's tent") 
      {
      write("You step into the confines of the tent.\n");
      TP->move_living("into the tent", INTR + "locket_shop");
      return 1;
   }
   write("Enter what? The tent?\n");
   return 1;
}

void
init()
{
    ::init();
    add_action(do_enter, "enter");
}
