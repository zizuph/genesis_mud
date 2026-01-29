// Bazaar Street24 (/d/Avenir/common/bazaar/extr/str24.c)
// creator(s):   Triana 1994
// last update:  Tepisch Sept 94, Ilyian May 95
// 		 Lucius Oct 2008
// purpose:
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/bazaar/extr/std_ctr2.c";
#include "/d/Avenir/common/bazaar/bazaar.h"

public static object guard1, guard2;

public void
create_room(void)
{
   AE(EXTR + "str23",     "north", 0);
   AE(INTR + "apoth",     "east",  0);
   AE(VILL + "merc/conn", "south", 0);

   AI("building", "It looks eerie.\n");
   AI("flag", "This piece of cloth hanging above the doorway "+
      "has a skull and crossbones stitched on it.\n");
   ACI("flag", "read", "Below the ominous image of a skull "+
     "and crossbones are stitched the letters: Apothecary.\n");
   AI("shingle", "A part of the roof that extends outward "+
     "and parallel to the ground.\n");

   SHORT("Gravel path between the apothecary and the garden");
   make_the_room(" The gravel path ends here, turning instead to "+
      "cobblestones heading south. East of you is a tall gray building.\n");

   add_npc(BAZAAR + "NPCS/grd", 2, &->arm_me());
}

