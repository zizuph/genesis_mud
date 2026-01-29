/*
 * orc2.c
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
    default_config_npc(10);

    set_short("orc child");
    set_pshort("orc children");
    set_long("The orc child grins at you with its sharp teeth.\n");
    set_gender(random(2));
    set_name("child");
    set_pname("children");
    add_name("orcbaby");
    set_race_name("orc");

    set_alignment(-20);

    seteuid(getuid(TO));

    if (!(H)->request_orc())
        set_alarm(0.0, 0.0, "remove_object");
    else
        registered = 1;
}

void
equip_me()
{
    clone_object(ROKEDIR + "arm/bucket")->move(TO);
    command("wear all");
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
    return 40;
}
