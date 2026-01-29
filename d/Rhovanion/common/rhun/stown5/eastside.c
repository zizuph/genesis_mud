
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("Small path");
set_long(break_string("This is the eastern side of this small, abandoned"
	+" town.  A narrow, hardly-discernable path leads west from"
	+" here.You may enter a small wooden building to the north,"
	+" or head off into the forest to the east."
	+"\n",75));

AE(RHUN+"stown5/empty_ne","north",0);
AE(RHUN+"stown5/crossroads", "west", 0);
AE(RHUN+"forest/l13", "east", 0);

add_prop(ROOM_I_LIGHT,1);

}

