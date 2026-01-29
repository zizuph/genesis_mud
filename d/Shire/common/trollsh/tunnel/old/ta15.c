/*
 * Tunnel beneath the Trollshaws
 * By Finwe, August 2001
 */
 

#pragma strict_types

inherit "/d/Shire/std/room.c";
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

inherit TUNNEL_BASE;

void
create_tunnel_room()
{
    set_long("@@tunnel_desc4@@");
    add_my_desc("Piles of bones are scattered about. They look " +
        "like they were gnawed on and broken into pieces.\n");
    set_add_bones();


    add_exit(TUN_DIR + "ta16", "east");
    add_exit(TUN_DIR + "ta14", "southwest");

    reset_shire_room();
}


void reset_shire_room()
{
        make_trolls();     
}

