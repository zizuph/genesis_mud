/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

create_icewall_room() {
   set_short("Front of Pass");
   set_long(
      "You stand before a mighty pass cutting through the "
      + "mountains of Icewall. It appears to be carved, but "
      + "not by human hands. The forest of ice is back along the path. "
      + "\n");
   
   add_item("mountains","There is a pass here going between them.\n");
   add_item("pass","It cuts through the mountains.\n");
   add_cmd_item("pass","enter","@@pass");
   
   add_exit(ICE_FOREST+"forest_14","southwest");
}
string pass() {
   write("You step carefully into the narrow pass.\n");
   set_dircmd("pass");
   say(QCTNAME(TP)+" disappears into the mountain pass.\n");
   tell_room(ICE_FOREST+"waterfall",QCTNAME(TP)+" steps out "
      + "of the mountain pass.\n");
   TP->move_living("M",ICE_FOREST+"waterfall",0,0);
   return "";
}
