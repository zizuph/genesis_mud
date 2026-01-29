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
   set_short("The Bywater road outside the village");
   set_long("You are now standing outside the village Hobbiton. "
    + "Westwards is the centre of the small village and to east "
    + "the road ends, and the wilderness begins.\n");

   add_exit(STAND_DIR + "bw_road6","west");
//   add_exit("/d/Shire/common/downs/hobbitlink","east",0);

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
}
