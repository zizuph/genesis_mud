/*
 *  Hallway underneath the mountain
 */

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "defs.h"

create_room() {
   set_short("Hallway");
   set_long(break_string(
      "You are in a hallway below a mountain. The hallway has been carved "
    + "out of the rocks ages ago. The floor is made of shiny, cold marble. "
    + "On the walls are many torches lighting the hallway. To the west is "
    + "some kind of guard room. South you can make out an opening which "
    + "seems to lead to the outside, while north the hallway continues.\n",70));

   add_item(({"torch","torches"}), break_string(
      "The torches have been secured to the walls. The light "
    + "of the torches is bright enough to light the hallway as if it was "
    + "the sun shining in here.\n",70));

   add_item(({"floor","marble","marble floor"}), break_string(
      "The marble floor feels cold. The white, shiny surface of the "
    + "marble tiles reflects the light of the torches, which makes the "
    + "room more bright.\n",70));

   add_exit(HINROOM_DIR + "hall2","north");
   add_exit(HINROOM_DIR + "guard","west");
   add_exit(HINROOM_DIR + "cave_ent","south");

   add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */
}
