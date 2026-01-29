inherit "/std/room";

#include "/sys/stdproperties.h"
#include "defs.h"

create_room() {
   set_short("Basement of little house");
   set_long(break_string(
      "You have entered the basement of the little house. This is what used "
    + "to be the secret wine-cellar of the owner of the house. Used to be, "
    + "because there is little left of the wine-barrels that stood here "
    + "once. Empty bottles are strewn across the dusty floor.\n",70));

   add_item(({"bottles", "empty bottles"}), break_string(
      "The empty bottles all carry the same label and have been emptied "
    + "a long time ago, because you do not smell any wine in them.\n",70));

   add_item(({"label","labels"}), break_string(
      "The labels of the empty wine-bottles say: \"Chateau Balings\"."
    + "You guess that Balings must be the owner of this house.\n",70));

   add_exit(STAND_DIR + "wf_house1", "up");

   add_prop(ROOM_I_INSIDE, 1); /* This room lies under the ground */
}
