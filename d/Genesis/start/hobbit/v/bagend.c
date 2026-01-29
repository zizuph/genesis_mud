/*
 *  Entrance to Bag End, the home of Bilbo Baggins
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("Bag End");
   set_long("You are standing on the front porch of a big looking house with a "
    + "round door. Beside the door is a plaque with a name on it. On the "
    + "doorknob hangs a sign.\n");

   add_item("sign", "The sign says: I'm away on a journey, B.B.\n");
   add_item("plaque", "On the plaque you read: 'Bilbo Baggins'.\n");
   add_item("door",
      "The door is shut tight, and you cannot possibly budge it.\n");
   add_item("doorknob", "It's just a simple doorknob made of wood.\n");

   add_exit(STAND_DIR + "h_lane5","south");

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
}

init() {
   ::init();
   add_action("do_read","read",0);
}

do_read(str) {
   if (str != "sign") return 0;
   write("The sign says: I'm away on a journey, B.B.\n");
   return 1;
}