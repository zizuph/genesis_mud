/*Created by Stevenson*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

init() {
   ADA("south");
   ::init();
}

create_icewall_room() {
   set_short("Tunnel Entrance");
   
   set_long(
      "You are in a dark and slippery room. The chill penetrates your "
      + "clothing and causes you difficulty in breathing. In the "
      + "south wall is a large hole, and north, the tunnel "
      + "continues towards the unknown. "
      + "\n");
   
   add_cmd_item("hole","enter","Why not just go south?\n");
   add_item("tunnel","It continues north.\n");
   add_item("unknown","HINT: Search the bed in the master bedroom. :)\n");
   add_item("wall","There is a large hole in it.\n");
   add_item("hole","The hole is large enough to walk into.\n");
   
   add_exit(QUEST+"path2","north");
}

int south() {
   write("You climb through the hole.\n");
   say(QCTNAME(TP)+" climbs through the hole in the south wall.\n");
   tell_room(QUEST+"dryland",QCTNAME(TP)+" arrives through the hole in the "
      + "north wall.\n");
   TP->move_living("M",QUEST+"dryland",0,0);
   return 1;
}
