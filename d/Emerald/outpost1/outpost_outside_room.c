#include "defs.h"

inherit OUTPOST_ROOM;
inherit "/d/Emerald/lib/room_tell";

void
create_outpost_outside_room()
{
    set_short("Outpost room");
    set_em_long("Outside the outpost.\n");
}

nomask void
create_outpost_room()
{
    set_tell_time(60);
    add_tell("Birds chirp in the distance.\n");
    create_outpost_outside_room();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    start_room_tells();
}
