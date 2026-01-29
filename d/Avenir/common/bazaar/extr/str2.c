// Bazaar Street2 (/d/Avenir/common/bazaar/extr/str2.c)
// creator(s):   Triana 1994
// last update:  Tepisch Aug 94, Ilyian May 95
// purpose:
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/bazaar/extr/std_ctr2.c";

#include "/d/Avenir/common/bazaar/bazaar.h"

object slave1, slave2, clock;
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
    if (!clock)
    {
        clock = clone_object("/d/Avenir/common/obj/clepsydra");
        clock->move(this_object());
    }
        
}

void
create_room()
{
   AE(INTR + "library" , "west", 0);
   AE(INTR + "bank", "east", 0);
   AE(EXTR + "str3", "south", 0);

   SHORT("Between the library and the bank");
   make_the_room(" To the north the gravel path continues, "+
      "while walking south will take you deeper into the "+
      "bazaar. West is the local library, and across from "+
      "it you can see the stately Bank of Sybarus.\n");

  AE(INTR+"d_str1", "north", 0);
    reset_room();
}

do_crunch()
{
   write("You stumble in the loose gravel.\n");
}

temp_block()
{
    write("The library is temporarily closed by order of the High Commissoner.\n");
    return 1;
}
