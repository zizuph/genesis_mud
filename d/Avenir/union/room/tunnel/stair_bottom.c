#pragma strict_types

#include "defs.h"
inherit SBASE;

public void
tunnel_room(void)
{
    ::tunnel_room();

    add_exit("tunnel1", "down");
    add_exit("stair_top", "up", -8, 3);
}
