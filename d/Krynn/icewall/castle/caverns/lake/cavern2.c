/*Created by Stevenson*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <stdproperties.h>
inherit ICEINROOM;

object eel;

create_icewall_room()
{
   set_short("Underground Lake");
   set_long(
      "You are at the northern edge of the underground lake. "
      + "The cavern wall looms directly before you. Off to the "
      + "east you see the water flowing down a passage. "
      + "\n");
   
   add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
   add_item("lake","It is nearly frozen.\n");
   add_item("wall","The cavern wall is roughly hewn by the lake very "
      + "slowly as time progresses. If you die, you "
      + "may even have the honour of becoming a part of it.\n");
   add_item("passage","The eastern passage slopes slightly downhill.\n");
   
   add_exit(CAVE+"cavern1.c", "south");
   add_exit(CAVE+"cavern3.c","east");
   
   reset_icewall_room();
}

reset_icewall_room()
{
   if(!eel)
      {
      eel = clone_object(ICE_CAST_M + "eel.c");
      eel->move(TO);
   }
}
