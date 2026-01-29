/****************************************/
/* West Hall of Icewall Castle*/
/* Coded by Steve*/
/****************************************/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>

inherit ICEINROOM;

create_icewall_room()
{
set_short("West Hallway");
        set_long(BS(
"\nYou are standing in a plain hallway that seems to lead"
+ " down to the accomodation area of the castle. Along the"
+ " walls of the hallway are a series of lamps that provide"
+ " the only light source. The hallway continues on to the"
+ " west and bends round to the south."
+ "",75));


add_item(({"lamp","lamps"}),
"There are ten lamps in total, five on each wall. Each has a gold\n"
+ "plated shade on it that reflects the light around the hall.\n");
add_item(({"shade","shades"}),
"Each of the shades is plated in 24 karat gold.\n");


add_exit(ICE_CAST1_R + "west_corner.c", "west");
add_exit(ICE_CAST1_R + "north_hall.c", "east");
}
