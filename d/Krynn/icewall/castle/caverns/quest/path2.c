/*Created by Stevenson*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

create_icewall_room() {
   set_short("Tunnel");
   
   set_long(
      "You are in a part of the tunnel that slopes up towards "
      + "some distant light source. In the distance you hear "
      + "water roaring. "
      + "\n");
   
   add_item("water","It is somewhere further up the tunnel.\n");
   add_item("tunnel","It is rough and misshapen.\n");
   
   add_exit(QUEST+"path1","south");
   add_exit(QUEST+"path3","up");
}
