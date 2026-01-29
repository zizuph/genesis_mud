/*
 * Bywater Road 
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("The Bywater road outside the post-office");
   set_long("This is the eastern part of Hobbiton. "
    + "There is a small building to the north, "
    + "it is the Hobbiton post office. South of the road is "
    + "a large, wooden barn. To the east the Bywater road "
    + "continues out towards the dwarven realm.\n");

   add_item(({"barn","wooden barn"}), 
      "The wooden walls of the barn have been tarred to make the barn "
    + "less leaky when it rains. The barn smells like straw and horses "
    + "or ponies.\n");

   add_exit(STAND_DIR + "p_office","north");
   add_exit(STAND_DIR + "stables","south");
   add_exit(STAND_DIR + "bw_road7","east");
   add_exit(STAND_DIR + "bw_road5","west");

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
}