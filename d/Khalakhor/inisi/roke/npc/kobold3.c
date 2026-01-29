/*
 * kobold3.c
 *
 * Used in wild/sh3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <ss_types.h>

void
create_monster()
{
    set_short("nasty kobold");
    set_long("The nasty kobold looks angrily at you!\n");
    set_name("kobold");
    set_adj("nasty");

    set_race_name("kobold");

    set_alignment(-100);

    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_DEFENCE, 5);

    default_config_npc(21);
}

int
query_knight_prestige()
{
    return 140;
}

void
equip_me()
{
    clone_object(ROKEDIR + "obj/torch")->move(TO);
    clone_object(ROKEDIR + "arm/fur")->move(TO);

    command("wear all");
}
