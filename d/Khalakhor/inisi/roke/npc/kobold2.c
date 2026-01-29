/*
 * kobold2.c
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
    set_short("hungry kobold");
    set_long("The hungry kobold has grim teeth that looks suitable for " +
             "eating knights.\n");
    set_name("kobold");
    set_adj("hungry");

    set_race_name("kobold");

    set_alignment(-100);

    set_skill(SS_UNARM_COMBAT, 10);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_WEP_KNIFE, 35);

    default_config_npc(35);
}

int
query_knight_prestige()
{
    return 200;
}

void
equip_me()
{
    clone_object(ROKEDIR + "arm/pigskin")->move(TO);
    clone_object(ROKEDIR + "wep/orc_knife")->move(TO);

    command("wear all");
    command("wield all");
}
