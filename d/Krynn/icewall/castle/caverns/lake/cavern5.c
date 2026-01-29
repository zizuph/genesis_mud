/*Created by Stevenson*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <stdproperties.h>
#include <macros.h>
inherit ICEINROOM;

create_icewall_room()
{
   set_short("Eastern Edge Of Lake");
   set_long(
      "You find yourself at the eastern edge of the underground lake. There "
      + "appears to be dry land both north and south of here. Far to the "
      + "south you can see large stalactites and stalagmites jutting from "
      + "floor and ceiling. "
      +"\n");
   
   add_item("lake","You are at the eastern edge of the lake. It stretches "
      + "both north and west of here.\n");
   add_item("land","It is more frozen than dry.\n");
   
   add_exit(CAVE+"cavern1.c","northwest");

   add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
   add_exit(CAVERNS+"cavern19.c","southeast");
}
