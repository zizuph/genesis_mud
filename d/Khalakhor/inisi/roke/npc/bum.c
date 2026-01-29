/*
 * bum.c
 *
 * Used in nyreese/red_r5.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

void
create_monster()
{
    int i;

    set_name("drifter");
    set_long("The filthy drifter is enjoying the warmth of the fire.\n");
    set_short("filthy drifter");

    set_race_name("drifter");
    set_adj("filthy");

    set_gender(0);

    set_skill(SS_WEP_CLUB, 5);
    set_skill(SS_PARRY, 5);

    for (i = 0; i < 6; i++)
        set_base_stat(i, 18);
    set_alignment(-5);

    ::create_monster();
}

void
equip_me()
{
    seteuid(getuid(TO));
    clone_object(ROKEDIR + "wep/club")->move(TO);
    command("wield all");
}

int
query_knight_prestige()
{
    return -1;
}
