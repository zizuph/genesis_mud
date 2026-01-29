/*
 *  The forest out side Hobbiton
 *  Finwe, April 2020 - Cleaned up description
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

create_room() {
   set_short("In a forest");
   set_long("You are standing just at the edge of a forest that belongs " +
        "to the goblins, that once was a big problem for the peaceful " +
        "Hobbiton. There is a small track between the trees that continues " +
        "west into the forest, where it ends.\n");

   add_item("track", "You can see some goblin footprints on the track.\n");

   add_exit("/d/Genesis/start/hobbit/v/bw_road1","east",0);

   add_prop(ROOM_I_INSIDE,0);  /* This is a outside room */
}
