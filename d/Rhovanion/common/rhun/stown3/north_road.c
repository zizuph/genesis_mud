
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
	+"  Just to the east lies a small wooden building."
	+"  There is also a small shop, which has just opened up to"
    +" the southeast."
	+"\n",75));

AE(RHUN+"stown3/crossroads", "north", 0);
AE(RHUN+"stown3/mid_road", "south", 0);
AE(RHUN+"stown3/e_home","east",0);
AE(RHUN+"stown3/shop","southeast");

add_prop(ROOM_I_LIGHT,1);

}
