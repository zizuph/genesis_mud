/*
 * Guard room in the Trollshaws
 * By Finwe, October 2001
 */
 

#pragma strict_types

#include "local.h"
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

inherit "/d/Shire/std/room.c";
inherit TUNNEL_BASE;

void
create_tunnel_room()
{
    set_short("A guard room in the Trollshaws");
    set_long("@@gr_desc1@@");
    add_my_desc("\n");
    set_add_guardroom_dirty();
    reset_shire_room();

    add_exit(TUN_DIR + "ta25", "south");
}

void reset_shire_room()
{
// clone_orcs
}
