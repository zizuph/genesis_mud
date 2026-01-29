#pragma strict_types

#include "defs.h"

inherit CRYPTBASE;
inherit CRYPTDOORS;

public void
reset_room()
{
    ::reset_room();
    reset_doors();
}

public void
create_room()
{
    create_crypt();

    add_exit(RUIN + "crypt_5", "west");
    add_crypt_door(RUIN + "e_tunnel_3", "east");

    set_alarm(0.0, 0.0, reset_room);
}

public void
init()
{
    ::init();
    init_doors();
}
