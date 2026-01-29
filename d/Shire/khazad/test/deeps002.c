
inherit "/d/Shire/khazad/moria_room_deeps";

#include "/d/Shire/khazad/defs.h"

void
create_deeps_room()
{
    set_deep(1);
    set_roomtype(0);
    set_extraline("@@add_extra@@");

    SOUTH("deeps001");
}

string
add_extra()
{
    if (this_player()->query_race_name() != "dwarf")
	return "Im not a dwarf!";

    return "I am a dwarf!";
}
