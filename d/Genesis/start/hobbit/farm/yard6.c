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
      "You are south of the main building of the farm. The entrance is not "
    + "on this side. Cattle seems to pass this place daily, as far as you "
    + "can tell by the marks in the sandy grass. Sounds of cattle are "
    + "coming from the barn to the southwest.\n");

   add_item(({"soil","grass","sandy grass"}),
      "Many animals must have walked here, since the sandy grass "
    + "contains many hoof and footprints. They lead from east to "
    + "west and vice versa.\n");

   add_exit(STAND_DIR + "yard5","east");
   add_exit(STAND_DIR + "yard7","west");

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */

   if(!present("snake"))
      clone_object(STAND_DIR + "snake")->move(this_object());
}

reset_room() {
   if(!present("snake"))
      clone_object(STAND_DIR + "snake")->move(this_object());
}