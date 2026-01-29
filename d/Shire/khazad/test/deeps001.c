
inherit "/d/Shire/khazad/moria_room_deeps";

#include "/d/Shire/khazad/defs.h"
#include <stdproperties.h>

void
create_deeps_room()
{
    set_deep(1);
    set_roomtype(0);
    set_extraline("@@add_extra@@");

    NORTH("deeps002");
}

string
add_extra()
{
    if (this_player()->query_prop(LIVE_S_LAST_MOVE) == "south") {
        return "002";
    }
	return "Im not a dwarf!";

}
