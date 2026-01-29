#pragma strict_types

inherit "/d/Earthsea/std/room.c";
inherit "/d/Earthsea/lib/room_tell";


#include "defs.h"

void create_city_road();


void
create_earthsea_room()
{
    set_short("The base room");
    set_long("This is just the basic room.\n");
    create_city_road();
    set_tell_time(120);
}

void
create_city_road()
{}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
	start_room_tells();
}
