
#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("Main street");
set_long(break_string("You are walking down this small town's main"
	+" street.  It leads off from here to the north and south."
	+"  Just to the west lies a moderately-sized wooden building,"
	+" perhaps the town guard-house."
	+"\n",75));

AE(RHUN+"stown3/north_road", "north", 0);
AE(RHUN+"stown3/bridge", "south", 0);
AE(RHUN+"stown3/guard_house","west",0);

add_prop(ROOM_I_LIGHT,1);

}
