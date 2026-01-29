#include "defs.h"

inherit OUTPOST_ROOM;
inherit "/d/Emerald/lib/room_tell";

void
create_outpost_outside_room()
{
}

nomask void
create_outpost_room()
{
    set_tell_time(300);
    add_tell("Birds chirp in the distance.\n");
    add_tell("A large eagle swoops through the sky above.\n");
    add_tell("A pigeon flies over your head and into the " +
             "watchtower in the middle of the outpost.\n");
    create_outpost_outside_room();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    start_room_tells();
}
