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
    + "The road runs from east to west. On both sides of the road are some "
    + "nice, small houses. The houses are surrounded "
    + "with a green hedge and have no windows. "
    + "To the north you can see the entrance to the "
    + "mayor's house. It looks very small for such an important person's "
    + "house. You can also see some hobbits walking down the road.\n");

   add_item("hedge","The hedge is green and looks well taken care off.\n");

   add_exit(STAND_DIR + "mayorhouse","north");
   add_exit(STAND_DIR + "bw_road4","east");
   add_exit(STAND_DIR + "bw_road1","west");

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
}
