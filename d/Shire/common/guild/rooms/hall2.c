/*
 *  Hallway underneath the mountain
 */

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "defs.h"

create_room() {
   set_short("Hallway");
   set_long(break_string(
      "You find yourself in a underground hallway. Nothing besides the "
    + "rock walls indicate that you are underground. The marble floor "
    + "feels cold under your feet. Many torches have been fastened "
    + "on the wall. West is some kind of shop. A weird fragrance comes "
    + "from it. The hallway continues both north and south.\n",70));

   add_item(({"torch","torches"}), break_string(
      "The torches cannot be removed from the walls. The light "
    + "of the torches is bright enough to light the hallway as if it was "
    + "the sun shining in here.\n",70));

   add_item(({"floor","marble","marble floor"}), break_string(
      "The marble floor feels cold. It is made of big white tiles "
    + "that lie beside each other with out the least sign of spacing "
    + "between them.\n",70));

   add_exit(HINROOM_DIR + "hall1","north");
   add_exit(HINROOM_DIR + "hall3","south");
   add_exit(HINROOM_DIR + "herbshop","west");

   add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */
   reset_room();
}

reset_room() {
  if (!present("torch")) clone_object(OBJ_DIR + "shoptorch")->move(this_room());
}
