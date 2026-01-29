/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

create_icewall_room()
{
   set_short("Uphill Path");
   set_long(
      "The walls are damp and clammy to the touch. Very little light is "
      + "here and soon you may need a torch. "
      + "\n");
   
	add_item(({"walls", "wall"}), "The walls are rough and studded with outcroppings.\n");
   add_item(({"outcropping","outcroppings"}),"One outcropping appears "
      + "to be twistable.\n");
   add_cmd_item("outcropping","twist",VBFC("gotobrag"));
   
   add_exit(CAVERNS + "cavern11.c", "west");
   add_exit(CAVERNS + "cavern13.c", "east");
}

string gotobrag() {
   write("You twist the outcropping and reveal a hidden passage in the "
      + "south wall which you didn't see before. You quickly enter it as "
      + "it begins to close again.\n");
   say("You hear a click and " + QTNAME(TP) + " is gone.\n");
   tell_room(CAVERNS+"cavern10",QCTNAME(TP)+" slides into the room.\n");
   TP->move_living("M",CAVERNS+"cavern10",1); /* don't follow */
   return "";
}
