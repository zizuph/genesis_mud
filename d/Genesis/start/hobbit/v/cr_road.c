/*
 * Crossroad 
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("Crossroad");
   set_long("This is the intersection of the two big "
    + "roads that run through Hobbiton. North and south runs "
    + "Hill lane, east and west Bywater road. "
    + "Far to the north is a quite big hill. "
    + "A few yards to the south is something that looks like "
    + "a well visited place.\n");

   add_exit(STAND_DIR + "h_lane1","north");
   add_exit(STAND_DIR + "h_lane2","south");
   add_exit(STAND_DIR + "bw_road5","east");
   add_exit(STAND_DIR + "bw_road4","west");

/*
   clone_object("/d/Genesis/obj/wizquest/mage_stone")->move(this_object());
*/
   add_prop(ROOM_I_INSIDE,0);  /* This is an open air room */
}