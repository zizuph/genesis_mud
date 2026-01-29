#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

create_icewall_room()
{
   set_short("hallway");
   set_long(BS(
         "This is the end of the corridor.  The corridor runs north and a door"
         + " to the west makes you feel trapped.",75));
   
   add_item("door","It is a door alright.\n");
   add_exit(ICE_CAST2_R + "hall5_2.c", "north");
   add_exit(ICE_CAST2_R + "guest1.c", "west");
}
