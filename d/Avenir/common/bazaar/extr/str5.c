// Bazaar Street5 (/d/Avenir/common/bazaar/extr/str5.c)
// creator(s):   Triana 1994
// last update:  Lilith Sept 97: added nygel the mummer
//               Tepisch Aug 94, Ilyian May 95
// purpose:
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/bazaar/extr/std_center.c";

#include "/d/Avenir/common/bazaar/bazaar.h"

object mummer, child1, child2;

void 
reset_room()
{
    if (!mummer)
    {
        mummer = clone_object("/d/Avenir/common/clubs/mummer/nygel");
        mummer->equip_me();
        mummer->move_living("M", this_object());
    }
    if (!child1)
    {
        child1 = clone_object(BAZAAR + "NPCS/ch1.c");
        child1->arm_me();
        child1->move_living("M", this_object());
    }
    if (!child2)
    {
        child2 = clone_object(BAZAAR + "NPCS/ch1.c");
        child2->arm_me();
        child2->move_living("M", this_object());
    }
}
void
create_room()
{
   AE(EXTR + "str4", "west", 0);
   AE(EXTR + "str6", "east", 0);
   AE(EXTR + "str12", "south", 0);
   AE(INTR + "main_menshop", "tent", 0);
   AI("building", "One of your typical places of business. This " +
     "one would appear to be a smithy. You can't see the " +
     "entrance from here.\n");

   SHORT("Northwest corner of Bazaar");
   make_the_room("\n   To the west the cobblestone square gives " +
      "way to a gravel path.\nA long, blue tent shop stands here, "+
      "preventing your progress north.\n");
   add_item(({"tent", "blue tent" , "long tent", "north", "flaps" }),
      "There is a long, blue tent here, with the front flaps thrown "+
      "wide open. There is a sign with big letters on it.\n");
   add_item(({"sign", "letters", "big letters" }), "The sign reads:\n"+
      "    Emarus the Tailor: Custom-designed and ready-to-wear\n"+
      "                       clothing for the men of Sybarus.\n");
   add_cmd_item(({"sign", "letters", "big letters" }), "read",
      "The sign reads:\n"+
      "    Emarus the Tailor: Custom-designed and ready-to-wear\n"+
      "                       clothing for the men of Sybarus.\n");
  reset_room();
}

