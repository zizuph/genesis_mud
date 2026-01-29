
inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

void
create_room()
{
    set_short("On the River Celduin");
    set_long(break_string("The river begins to curve here from"
	+" northwest to east.  It flows ever on, with no end in sight."
	+"  You can only sit and wait."
	+"\n",75));
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
