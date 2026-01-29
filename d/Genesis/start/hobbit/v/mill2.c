/*
 *  The watermill, upstairs
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

int wheel_fixed;

create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("Watermill attic");
   set_long("You are in the attic of the sawing mill. It is used to store "
    + "things that are no longer needed anymore. However, it must "
    + "have been cleaned lately, since there is not much here.\n");

   add_exit(STAND_DIR + "mill","down",0);

   add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

   if (!present("mill_hammer"))
      clone_object(STAND_DIR + "hammer")->move(this_object());
}

reset_room() {
   if (!present("mill_hammer") && !random(3))
      clone_object(STAND_DIR + "hammer")->move(this_object());
}