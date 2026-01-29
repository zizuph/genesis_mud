#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"
#pragma save_binary

inherit RHUN + "stowns/guard_master";

create_room()
{
set_short("Guard house");
set_long(break_string(
	"You stand in a guard house in this rather"
	+" large town near the Sea of Rhun.  The entire building--"
        +" quite large and spacious -- is made of wood.  This"
	+" is obviously a resting place for the town guards."
	+"  The only exit lies west, back onto the street."
	+"\n",75));

AE(RHUN+"ltown_sw/streets/st5","west",0);

add_prop(ROOM_I_LIGHT,1);IN

    reset_room();
}
