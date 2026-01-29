/*Created by Stevenson*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <stdproperties.h>
inherit ICEINROOM;

object eel;

void
create_icewall_room()
{
   set_short("Tight Passage");
   set_long(
      "The lake begins to flow downhill at this point through a "
      + "tight passage to the northeast. Stalactites are poking from "
      + "above so watch your head. "
      + "\n");
   
   add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
   add_item("walls","There appears to be writing on one of the walls.\n");
   add_item("writing","You see: Macker and Stevenson were here first!\n");
   add_item("lake","The lake is very cold and causes you to shiver.\n");
   add_item("stalactites","They stick out of the ceiling and could hurt "
      + "if you were bump your head into one of them.\n");
   add_item("ceiling","There are stalactites sticking down from it.\n");
   
   add_exit(CAVE+ "cavern2.c","west");
   add_exit(CAVE+ "cavern1.c", "southwest");
   add_exit(CAVE+ "cavern15.c", "northeast","@@squeeze");
   
   set_alarm(1.0,0.0,"reset_icewall_room");
}

int
squeeze() {
   write("You squeeze carefully between the walls.\n");
   return 0;
}

reset_iceall_room()
{
   if(!eel)
      {
      eel = clone_object(ICE_CAST_M + "eel.c");
      eel->move(TO);
   }
}
