
inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

void
create_room()
{
    set_short("On the River Celduin");
    set_long(break_string("The River Celduin, often called the River"
	+" Running, stretches out here, flowing from west to"
	+" east.  Just east of here, you can see a pier where it"
	+" joins the River Carnen and begins to flow off to the"
	+" southeast, toward the Sea of Rhun."
	+"\n",75));
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
