/* Vladimir 8-10-94 */
inherit "/std/room.c";

#include <macros.h>
#include "/sys/stdproperties.h"
#include "local.h"
#define TO this_object()

string long;
object orc;

create_room()
{
   set_short("Bunk room");
   set_long("In this room many orcs receive rest. The bunks are empty\n"
      + "at the moment though. Other than the bunks the room is\n"
      + "more or less empty. Occasionally you may catch an orc \n"
      + "getting ready to doze off to sleep.\n");
   add_item(({"bunks", "beds"}),
       "These bunks are little more than wooden boards stacked "+
         "on top of each other. They smell about as bad as their "+
         
    "owners.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_exit(ORC+"hall1", "west");
   
   reset_room();
}

reset_room()
{
   if(!orc)
      {
      orc = clone_object(ORC+"monsters/orc2");
      orc->move_living("xxx", TO);
   }
}
