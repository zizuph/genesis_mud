
inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

void
create_room()
{
    set_short("On the River Celduin");
	set_long(break_string("The Celduin flows from the north down to the"
	+" southeast here.  You stare from the ship's railing as the"
	+" forest of Mirkwood slips by on the west side.  To the east,"
	+" the plains of northeastern Rhovanion extend out for"
	+" as far as the eye can see."
	+"\n",75));
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
