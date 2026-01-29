#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include "/sys/stdproperties.h"
inherit ICEINROOM;

create_icewall_room()
{
set_short("hallway");
set_long(BS(
"You are standing in the upstairs hallway.  The corridor to the east"
+" bends north while to the west you can see the main staircase"
+" leading downstairs.",75));

add_exit(ICE_CAST2_R + "main_hall.c", "west");
add_exit(ICE_CAST2_R + "hall3_2.c", "east");
}
