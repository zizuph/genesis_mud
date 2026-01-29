/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <stdproperties.h>
inherit ICEINROOM;

create_icewall_room()
{
   set_short("Western Edge Of Lake");
   set_long(
      "You are at the exact western edge of the lake. A small path leads "
      +"to the west from here while the lake is to the east. "
      +"\n");
   
   add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
   add_item("path","It doesn't look too difficult to climb.\n");
   add_item("lake","The lake is virtually frozen but not enough that you "
      + "could walk on it.\n");
   
   add_exit(CAVE + "cavern1.c", "east");
   add_exit(CAVERNS + "cavern16.c", "west");
}
