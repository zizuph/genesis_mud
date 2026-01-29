/*
 * orc3.c
 *
 * Used in nyreese/orc_house.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* Gresolle 1992 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

void
create_monster()
{
    default_config_npc(15);

    set_short("orc teacher");
    set_long("This must be the kindergarten teacher.\n");
    set_name("teacher");
    set_race_name("orc");

    set_alignment(-50);
}

int
query_knight_prestige()
{
    return 65;
}
