
// Bazaar Street22 (/d/Avenir/common/bazaar/extr/str22.c)
// creator(s):   Triana 1994
// last update:  Tepisch Sept 94, Ilyian May 95
//		 Kazz May 95, opened exit to bakery
//               Lilith, Jun 96, added medallion seller
// purpose:
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/bazaar/extr/std_ctr2.c";

#include "/d/Avenir/common/bazaar/bazaar.h"

static object seller;

void
reset_room()
{
  if (!seller)
    {
      seller = clone_object(NPC + "medal_seller");
      seller->move_living("away", this_object());
    }
}

init()
{
   ::init();

   ADD("do_crunch", "north");
   ADD("do_crunch", "south");
}

void
create_room()
{
   AE(EXTR + "str19", "north", 0);
//   AE(INTR + "bakery", "east", "@@temp_block");
   AE(INTR + "bakery", "east", 0);
   AE(INTR + "shop", "west", 0);
   AE(EXTR + "str23", "south", 0);

   AI("building", "It looks like a bakery.\n");
   AI("shop", "The entrance is west.\n");
   AI("sign", "This piece of wood swinging from the shingle "+
      "has engraved upon it the image of a muffin glaring down "+
      "at you with a kitchen knife clenched in its doughy hand.\n");
   ACI(({"sign","bakery sign"}), "read", "Below the image of "+
     "a muffin glaring down at you with a kitchen knife "+
     "clenched in its hand are the words: The Moody Muffin.\n");
   AI("shingle", "A part of the roof that extends outward "+
     "and parallel to the ground.\n");

   SHORT("Gravel path between the Moody Muffin and a shop");
   make_the_room(" The gravel path continues in a north-"+
      "south direction. You see a shop to the west, while "+
      "in the east a sign hangs from a stone building that "+
      "smells like a bakery.\n");

   reset_room();
}

do_crunch()
   {
   write("You stumble as you trudge through the gravel.\n");
   }

temp_block()
    {
    write("The bakery is temporarily closed due to a recent fire.\n");
    return 1;
    }
