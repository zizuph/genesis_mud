
inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

void
create_room()
{
    set_short("On the River Carnen");
    set_long(break_string("The River Carnen flows along here from"
	+" west to east.  South of the river, you can see a small town."
	+"\n",75));
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
