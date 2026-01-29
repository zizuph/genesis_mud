
// Bazaar Street7 (/d/Avenir/common/bazaar/extr/str7.c)
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
   AE(EXTR + "str6", "west", 0);
   AE(EXTR + "str8", "east", 0);
   AE(EXTR + "str13", "south", 0);
   AE(INTR + "silkshop", "tent", 0);

   SHORT("Northeast corner of Bazaar, entrance to pink and green tent");
   make_the_room(" To the east the cobblestone square gives " +
      "way to a gravel walk.\nThere is a pink and green striped "+
      "tent before you.\n");
   AI(({"tent"}),"It is a pink and green striped tent. "
      +"You can enter it from this side.\n");
   AI(({"entrance", "tent entrance", "opening"}), 
      "It looks like it can be easily entered.\n");
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
      TP->move_living("into the tent", INTR + "silkshop");
      return 1;
   }
   write("Enter what? The tent?\n");
   return 1;
}



