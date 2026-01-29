#include "/d/Krynn/common/defs.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

create_icewall_room()
{
set_short("Castle Dungeons");
set_long(BS("You are in the corridor of the castle dungeons. The "
	+"walls are covered with slime, the air is damp, and "
	+"it smells really bad. The corridor continues south while "
	+"to the east and west are prison cells. To the north "
	+"is a solid door.",70));

add_item("slime",
"The slime is green and wet and looks like snot.\n");
add_item("cell",
"The cell doors seem to be unlocked.\n");

add_exit(BASE+"cellen","east",0);
add_exit(BASE+"cellwn","west",0);
add_exit(BASE + "prisons","south",0);
add_exit(BASE + "guard","north",0);
}
