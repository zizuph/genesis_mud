// Bazaar Street3 (/d/Avenir/common/bazaar/extr/str3.c)
// creator(s):   Triana 1994
// last update:  Tepisch Aug 94, Ilyian May 95
// purpose:
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/bazaar/extr/std_ctr2.c";

#include "/d/Avenir/common/bazaar/bazaar.h"

object poet;

init()
{
   ::init();
   ADD("do_crunch","north");
}

void
reset_room()
{
    if(poet)
       return;

    poet = clone_object(NPC + "poet");
      poet->arm_me();
      poet->move_living("XX", TO);
}

void
create_room()
{
   AE(EXTR + "str2", "north", 0);
   AE(INTR + "armr", "west", 0);
   AE(INTR + "post", "east", 0);
   AE(EXTR + "str6", "south", 0);

   SHORT("Between the post office and the smithy");
   make_the_room(" East is the entrance to a tidy "+
      "building with the letters 'B.I.P.S.' carved into the "+
      "stone facade. Across from it is the village Smithy."+
      " To the north the gravel path continues, while walking "+
      "south will take you deeper into the bazaar.\n");

    reset_room();
}

do_crunch()
   {
   write("Gravel crunches under your feet.\n");
   }
