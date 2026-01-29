/*
 *  The river, south of the farm
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("River");
   set_long("You are standing on one shore of the River Bywater. The water in "
    + "the river is clear and cold. In the water grow reeds, where "
    + "frogs sometimes hide. North from here is a little pasture, enclosed "
    + "by barbed wire.\n");

   add_item("water",
      "The water of the river Bywater is clear and cold. Perhaps too "
    + "cold for a bath. The water came all the way from the "
    + "hills to the west.\n");

   add_item(({"river","Bywater","bywater","river bywater"}),
      "The river Bywater comes from a spring in the hills to the west. "
    + "The water in it is clear and cold, and flows to the east.\n");

   add_item("reeds",
      "The reeds are about 5 feet high, and have brown plumes on the top. "
    + "Between them you can occasionally see a frog diving into the water.\n");

   add_exit(STAND_PARENT + "farm/yard8","north");

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
   add_prop(OBJ_I_CONTAIN_WATER, 1); /* There is water here */

   if(!present("frog"))
      clone_object(STAND_DIR + "frog")->move(this_object());
}

reset_room() {
   if(!present("frog"))
      clone_object(STAND_DIR + "frog")->move(this_object());
}