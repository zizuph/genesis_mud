#pragma strict_types

#include "defs.h"

inherit CRYPTBASE;
inherit TOMBDOORS;

public void
create_room()
{
    create_crypt();

    add_exit(RUIN + "crypt_5", "south", VBFC_ME("leave_tomb"));
    create_tomb(GURU_BRAIN->query_kings()[3], "north");
}

public void
init()
{
    ::init();
    init_tomb();
}

