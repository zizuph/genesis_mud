// Bazaar Street8 (/d/Avenir/common/bazaar/extr/str8.c)
// creator(s):   Triana 1994
// last update:  Tepisch Aug 94, Ilyian May 95
// purpose:
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/bazaar/extr/std_ctr2.c";

#include "/d/Avenir/common/bazaar/bazaar.h"
object hawker;

void
reset_room()
{
    if(!hawker)
    {
        hawker = clone_object(BAZAAR + "NPCS/pusher");
        hawker->arm_me();
        hawker->move(TO);
    }
}

void
create_room()
{
   AE(INTR + "butcher_shop", "north", 0);
   AE(INTR + "pub", "east", 0);
   AE(EXTR + "str14", "south", 0);
   AE(EXTR + "str7", "west", 0);

   AI("shingle", "A part of the roof that extends outward "+
     "parallel to the ground.\n");
   AI(({"sign","wooden sign"}), "A battered wooden sign upon " +
     "which is painted the image of a shackled man with blood "+
     "running from lash-marks on his back.\n");
   ACI(({"sign","wooden sign"}), "read", "Beneath the image of "+
     "a shackled man with blood running from lash-marks on his "+
     "on back are the words: Icky Bod's Pub.\n");

   SHORT("Outside Icky Bod's and the Butcher's");
   make_the_room("\n   A butcher shop has opened its "+
      "shutters in the building that lies to "+
      "the north.  A wooden sign hangs "+
      "outside a disreputable-looking establishment just "+
      "east of you.  Music, song, and the smell of stale "+
      "beer assaults your senses.\n");
   reset_room();
}

int
do_crunch()
{
    write("Gravel crunches under your feet.\n");
    return 0; 
}

int
do_body()
{
    write("You step on a drunk as you enter the pub.\n\n");
    return 0;
}

init()
{
   ::init();
   ADD("do_crunch","south");
   ADD("do_body", "east");
}
