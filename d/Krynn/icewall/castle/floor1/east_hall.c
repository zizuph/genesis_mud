/****************************************/
/* East Hall of Icewall Castle*/
/* Coded by Steve*/
/****************************************/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>

inherit ICEINROOM;

create_icewall_room()
{
set_short("East Hallway");
        set_long(BS(
"\nYou are standing in a plain hallway that seems to lead"
+ " down to the basement of the castle. Along the"
+ " walls of the hallway are a series of lamps that provide"
+ " the only light source. The hallway continues on to the"
+ " east and bends round to the south."
+ "",75));


add_item(({"lamp","lamps"}),
"There are ten lamps in total, five on each wall. Each has a gold\n"
+ "plated shade on it that reflects the light around the hall.\n");
add_item(({"shade","shades"}),
"Each of the shades is plated in 24 carrot gold.\n");


add_exit(ICE_CAST1_R + "east_corner.c", "east");
add_exit(ICE_CAST1_R + "north_hall.c", "west");
}
