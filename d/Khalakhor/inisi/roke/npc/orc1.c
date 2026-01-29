/*
 * orc1.c
 *
 * Used in nyreese/orc_house.c nyreese/orc_play.c nyreese/orc_sand.c 
 * Used in nyreese/orc_slide.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* Gresolle 1992 */
/*  added pshort and pname, Amelia, 7/97 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#define H ROKEDIR + "npc/orchandler"

int registered;

void
create_monster()
{
    default_config_npc(5);

    set_short("orc baby");
    set_pshort("orc babies");
    set_pname("babies");
    set_name("baby");
    add_name("orcbaby");

    set_alignment(-10);

    set_long("The baby is playing on the ground.\n");
    set_race_name("orc");


    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_VOLUME, 1000);

    seteuid(getuid(TO));
    if (!(H)->request_orc())
        set_alarm(0.0, 0.0, "remove_object");
    else
        registered = 1;
}

void
remove_object()
{
    if (registered)
        (H)->orc_died();
    ::remove_object();
}

int
query_knight_prestige()
{
    return 10;
}
