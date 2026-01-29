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
    set_long("@@tunnel_desc2@@");
    add_my_desc("A strong breeze blows from the east, smelling " +
        "rancid yet fresh similtaneously. A faint light comes " +
        "from there, too.\n");


    add_exit(TUN_DIR + "ta21", "west");
    add_exit(TS_DIR + "tunnel1", "east");


    reset_shire_room();
}


void reset_shire_room()
{
        make_trolls();     
}

