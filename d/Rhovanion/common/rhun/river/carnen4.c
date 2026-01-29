
inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

void
create_room()
{
    set_short("On the River Carnen");
    set_long(break_string("The River Carnen curves here from north to"
	+" southeast.  Just off to the northwest lies a small pier,"
	+" while the vast, empty plains of Rhun stretch off in all"
	+" directions from the river's edge."
	+"\n",75));
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
