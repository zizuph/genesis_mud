/*
 *  River2 
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("River Bywater");
   set_long("You are standing in the shadow of the bridge over the river "
    + "Bywater. Above you, you hear people walking over the bridge. "
    + "The river is filled with clear, cold water "
    + "from the hills. The river is too deep here to cross it. You can "
    + "follow the river to the east or the west.\n");

   add_item("water", 
      "The water of the river Bywater is clear and cold. Perhaps too "
    + "cold to take a bath in it. The water came all the way from the "
    + "hills to the west.\n");

   add_item(({"river","Bywater","bywater","river bywater"}), 
      "The river Bywater comes from a spring in the hills to the west. "
    + "The water in it is clear and cold, and flows to the east.\n");

   add_exit(STAND_DIR + "river3","east",0);
   add_exit(STAND_DIR + "river1","west",0);

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
   add_prop(OBJ_I_CONTAIN_WATER, 1); /* There is water here */
}