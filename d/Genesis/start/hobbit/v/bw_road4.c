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
   set_short("The Bywater road");
   set_long("You are standing on the Bywater road. "
    + "The road you are standing on continues both east and west. "
    + "To the east is something that looks like a crossroad. "
    + "To the north is the local bakery. You can smell "
    + "that they have fresh bread in there. South is the local pub.\n");

   add_exit(STAND_DIR + "bakery","north");
   add_exit(STAND_DIR + "pub","south");
   add_exit(STAND_DIR + "cr_road","east");
   add_exit(STAND_DIR + "bw_road2","west");

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
}