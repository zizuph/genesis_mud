#include "../defs.h"
inherit "/d/Emerald/std/room";

void
create_nthmount_room()
{
}

nomask void
create_emerald_room()
{
    create_nthmount_room();
}

add_mtcave()
{
    set_short("Inside A Cave");
    set_em_long("You are inside a large cave.\n");
}
