/*
 *  The house of the mayor of Hobbiton
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

create_room()
{
   object rug;

   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("Inside the Mayors house");
/* The rug shouldn't be fixed in the longdesc of the room! /Tintin */
   set_long("You are inside the house of the Mayor of Hobbiton. "
    + "The house is much bigger on the inside than it looks from the "
    + "outside. The walls are covered with many paintings of important "
    + "people who have contributed to the well-being of Hobbiton. "
    + "To the north the Mayor receives his guests and to the "
    + "south you can leave this house.\n");

   add_item(({"painting","paintings"}), 
      "You see paintings of some Bagginses, notably Bilbo and his nephew "
    + "Frodo, some Tooks, some Brandybucks and one painting of old Gaffer "
    + "Gamgee.\n");

   add_exit(STAND_DIR + "bw_road2","south",0);
   add_exit(STAND_DIR + "mayorhouse2", "north", 0);

   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

   if (!present("rug")) {
      rug = clone_object(STAND_DIR + "rug");
      rug->move(this_object());
   }
}
