
inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

void
create_room()
{
    set_short("On the River Carnen");
    set_long(break_string("You travel the length of the River"
	+" Carnen.  From here, it approaches a small town to"
	+" the southeast.  Vast, empty plains stretch out to"
	+" the north and south, as the river continues west."
	+"\n",75));
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
