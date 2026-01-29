/*
 * pimp.c
 *
 * Used in nyreese/red_bordell.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

void
create_monster()
{
    /*set_name("baihurk");*/
    NEVERKNOWN;
    set_race_name("goblin");
    add_name("goblin");
    add_name("pimp");
    set_long("He is dressed in rather fancy clothes.\n");

    default_config_npc(35);
}

int
query_knight_prestige()
{
    return 112;
}
