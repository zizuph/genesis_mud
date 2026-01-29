/*Created by Stevenson*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

create_icewall_room() {
   set_short("Tunnel");
   set_long(
      "You are in a rounded tunnel, perhaps worn to its smoothness "
      + "by the passing of water over the years. All that is left "
      + "of the once mighty torrent is a small trickle coming "
      + "from the east and heading down into darkness. "
      + "\n");
   
   add_item("water","It is just a small trickle.\n");
   add_item(({"cave","walls","ceiling","floor"}),
      "The tunnel walls are quite smooth.\n");
   
   add_exit(QUEST+"path2","down");
   add_exit(QUEST+"cave","west");
}
