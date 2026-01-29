/****************************************/
/*    North Hall of Icewall Castle */
/*       Coded by Steve*/
/****************************************/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>

inherit ICEINROOM;

create_icewall_room()
{
set_short("North Hall");
set_long(BS(
"\nYou are standing in the smaller part of the hallway in the"
+ " castle. The smell of burning wood is now much stronger and"
+ " seems to be coming from behind the door to the north. There"
+ " are hallways running east and west and the underside of"
+ " the great stairs towers above your head."
+ "",75));


add_item(({"underside","stairs"}),
"The stairs leading up to the second floor lie to your south.\n");

add_exit(ICE_CAST1_R + "oak_room.c", "north");
add_exit(ICE_CAST1_R + "main_hall.c", "south");
add_exit(ICE_CAST1_R + "east_hall.c", "east");
add_exit(ICE_CAST1_R + "west_hall.c", "west");
}
