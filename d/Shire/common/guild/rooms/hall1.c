/*
 *  Hallway outside the guildroom 
 */

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "defs.h"

create_room() {
   set_short("Hallway");
   set_long(break_string(
      "You are standing in a hallway underneath a mountain. The floor is "
    + "made of marble, and reflects the light of the torches on the "
    + "wall. The hallway leads south, and north is a room that looks "
    + "like the Hin Warrior Post Office. To the east is "
    + "a well-visited entrance.\n",70));

   add_item(({"torch","torches"}), break_string(
      "The torches have been fastened securely to the walls. The light "
    + "of the torches is bright enough to light the hallway as if it was "
    + "the sun shining in here.\n",70));

   add_item(({"floor","marble","marble floor"}), break_string(
      "The marble floor feels cold. It has been polished not long ago, "
    + "so the light of the torches is reflected very brightly in it.\n",70));

   add_exit(HINROOM_DIR + "hguild","east");
   add_exit(HINROOM_DIR + "hall2","south");
   add_exit(HINROOM_DIR + "libr1","west");
   add_exit(HINROOM_DIR + "post","north");

   add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */
}
