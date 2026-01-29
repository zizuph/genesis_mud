/*
 * troll.c
 *
 * Used in wild/p2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <ss_types.h>

void
create_monster()
{
    set_short("nasty troll");
    set_long("The nasty troll stares hungrily at you.\n");
    set_name("troll");
    set_adj("nasty");

    set_race_name("troll");

    set_alignment(-200);

    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_DEFENCE, 30);

    default_config_npc(50);
}

int
query_knight_prestige()
{
    return 100;
}

void
equip_me()
{
    clone_object(ROKEDIR + "obj/torch")->move(TO);
    clone_object(ROKEDIR + "arm/fur")->move(TO);

    command("wear all");
}
