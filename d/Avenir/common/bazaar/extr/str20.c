// Bazaar Street20 (/d/Avenir/common/bazaar/extr/str20.c)
// creator(s):   Triana 1994
// last update:  Tepisch Aug 94, Ilyian May 95
// purpose:
//
// note:         added hawker for the junkshop tent
// bug(s):
// to-do:


inherit "/d/Avenir/common/bazaar/extr/std_center.c";

#include "/d/Avenir/common/bazaar/bazaar.h"

object hawker, slave1;

void
reset_room()
{

  if (!slave1)
    {
      slave1 = clone_object(BAZAAR + "NPCS/wom1.c");
      slave1->arm_me();
      slave1->move_living("away", this_object());
    }

  if (!hawker)
    {
      hawker = clone_object(BAZAAR + "NPCS/jhawker.c");
      hawker->arm_me();
      hawker->move_living("away", this_object());
    }
}

void
create_room()
{
   AE(EXTR + "str13", "north", 0);
   AE(EXTR + "str19", "west", 0);
   AE(EXTR + "str21", "east", 0);
   AE(INTR + "junk", "tent", 0);

   AI(({"tent"}),"It is a dingy three-sided tent. "
      +"You can enter it from this side.\n");
   AI(({"entrance", "tent entrance", "opening"}), 
      "It looks like it can be easily entered.\n");
   SHORT("Southeast end of Bazaar, at entrance to a junk shop");
   make_the_room("\n   To the east the cobblestone square gives " +
      "way to a gravel path. The heady aroma of fresh-baked " +
      "bread wafts from the building to the south. There is "+
      "a grubby merchant's tent here.\n");
   reset_room();
}

void
init()
{
  ::init();
  ADD("do_enter", "enter");
}

int
do_enter(string str)
{
   if (str=="tent" || str== "merchant's tent") 
      {
      write("You step into the confines of the tent.\n");
      TP->move_living("into the tent", INTR + "junk");
      return 1;
      }
   NF("Enter what?\n");
   return 0;
}


