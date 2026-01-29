/*
 * kobold1.c
 *
 * Used in wild/sh3.c
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
    set_short("tired kobold");
    set_long("The tired kobold wants to go to sleep.\n");
    set_name("kobold");
    set_adj("tired");

    set_race_name("kobold");

    set_skill(SS_PARRY, 15);
    set_skill(SS_DEFENCE, 15);

    set_skill(SS_WEP_POLEARM, 30);

    default_config_npc(20);

    set_alignment(-100);
}

int
query_knight_prestige()
{
    return 200;
}

void
equip_me()
{
    clone_object(ROKEDIR + "arm/lboots")->move(TO);
    clone_object(ROKEDIR + "wep/spear")->move(TO);

    command("wear all");
    command("wield all");
}
