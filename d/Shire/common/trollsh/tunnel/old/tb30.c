/*
 * Tunnel beneath the Trollshaws
 * By Finwe, August 2001
 */
 

#pragma strict_types

inherit "/d/Shire/std/room.c";

#include "local.h"
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

inherit TUNNEL_BASE;
int clone_trolls = random(2);

//int max_trolls = random(3);
//static object *trolls  = allocate(max_trolls);

void
create_tunnel_room()
{
    set_long("@@tunnel_desc3@@");
    add_my_desc("The passage takes a sharp turn heading north " +
        "and southeast.\n");

    add_exit(TUN_DIR + "tc08", "north");
    add_exit(TUN_DIR + "tbg07", "east");
    add_exit(TUN_DIR + "tb22", "southeast");

    reset_shire_room();
}

void reset_shire_room()
{
    make_trolls();
}

