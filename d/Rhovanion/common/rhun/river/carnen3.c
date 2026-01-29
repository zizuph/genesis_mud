
inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

void
create_room()
{
    set_short("On the River Carnen");
    set_long(break_string("Only empty plains line the river as you head"
	+" along it.  Off to the south, a road travels parallel to the"
	+" riverbank, heading east to west."
	+"\n",75));
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
