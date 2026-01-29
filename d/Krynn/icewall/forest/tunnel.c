/* Created by Stevenson */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

create_icewall_room() {
   set_short("Inside Tunnel");
   set_long(
      "You enter a dark tunnel.  You can hear water dripping from the "
      + "ceiling.  In front of you is pure, inky blackness. "
      + "\n");
   
   add_item("blackness","Considering how dark it is, there isn't much to see.\n");
   add_item("water","You cannot make out the source of the dripping.\n");
   add_item("tunnel","It is very rough and and uneven.\n");
   add_item("ceiling","It is rough and most likely was created by some "
      + "mighty force of nature.\n");
   add_exit(ICE_PLAINS+"tunnel","up");
   add_exit(ICE_FOREST+"forest_10","out");
   
   DARK
}
