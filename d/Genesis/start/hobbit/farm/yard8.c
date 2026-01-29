/*
 *  The yard of the farm
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("Yard");
   set_long(
      "This is the pasture where the cattle of the farm is when "
    + "they are not inside the barn. The pasture is surrounded by barbed "
    + "wire on all sides, except the south side where the river Bywater "
    + "prevents the cattle from going that way.\n");

   add_item(({"wire","barbed wire"}),
      "The barbed wire prevents the animals from going where they are not "
    + "supposed to go.\n");

   add_exit(STAND_DIR + "yard5","north");
   add_exit(STAND_PARENT + "v/river4","south");

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */

   if(!present("bee"))
      clone_object(STAND_DIR + "bee")->move(this_object());
}

reset_room() {
   if(!present("bee"))
      clone_object(STAND_DIR + "bee")->move(this_object());
}