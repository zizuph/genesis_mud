/* Created By Stevenson */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

create_icewall_room() {
   set_short("Up/Down Stairs");
   set_long(
      "You are currently on a steep set of stairs carved into the face of "
      + "the ice.  They go both up and down. "
      + " \n");
   
   add_item("ice","It is very cold and hard.\n");
   add_item("stairs","They run up and down the ice.\n");
   add_exit(ICE_OUT+"bottom_of_ice","down");
   add_exit(ICE_OUT+"up_stairs2","up");
}
