// Bazaar Street12 (/d/Avenir/common/bazaar/extr/str12.c)
// creator(s):   Triana 1994
// last update:  Tepisch Aug 94, Ilyian May 95
// purpose:
//
// note:
// bug(s):
// to-do:


inherit "/d/Avenir/common/bazaar/extr/std_center.c";

#include "/d/Avenir/common/bazaar/bazaar.h"

object slave1, slave2, slave3, fisherman, hawker;

void
reset_room()
{

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
   if(!fisherman)
   { 
      fisherman = clone_object(BAZAAR + "NPCS/fisherman");
      fisherman->arm_me();
      fisherman->move(TO);
   }
   if(!hawker)
   {
      hawker = clone_object(BAZAAR + "NPCS/hhawker");
      hawker->arm_me();
      hawker->move(TO);
   }
}

void
create_room()
{
   AE(EXTR + "str5", "north", 0);
   AE(EXTR + "str11", "west", 0);
   AE(EXTR + "centr", "east", 0);
   AE(EXTR + "str18", "south", 0);
   AE(INTR + "hatshop", "tent", 0);

   AI("tent", "It is a green-striped tent with a "+
      "sign shaped like a hat hanging before the entrance.\n");
   AI("sign", "It reads:     Heboba's Hat Shop\n");
   ACI("sign", "read", "It reads:    Heboba's Hat Shop\n");
   AI(({"entrance", "tent entrance", "opening"}), 
      "It looks like it can be easily entered.\n");

   SHORT("East corner of Bazaar. Entrance to a green-striped tent");
    make_the_room("\n   To the west the cobblestone square gives " +
      "way to a gravel path, while just before you stands a green-striped tent.\n");
   
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
   if (str=="tent" || str== "green tent") 
      {
      write("You step into the confines of the tent.\n");
      TP->move_living("into the tent", INTR + "hatshop");
      return 1;
   }
   write("Enter what? The tent?\n");
   return 1;
}

