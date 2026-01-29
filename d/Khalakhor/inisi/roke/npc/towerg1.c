/*
 * towerg1.c
 *
 * Used in nyreese/cas_t11.c nyreese/cas_t12.c
 * Used in nyreese/cas_t13.c nyreese/cas_t14.c
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
equip_me()
{
    clone_object(ROKEDIR + "wep/spear")->move(TO);
    clone_object(ROKEDIR + "arm/lboots")->move(TO);
    clone_object(ROKEDIR + "arm/chelmet")->move(TO);
    clone_object(ROKEDIR + "arm/cpmail")->move(TO);

    command("wear all");
    command("wield all");
}

void
create_monster()
{
    set_name("guard");
    set_short("tower guard");
    set_long("The guard is guarding the towers from people like you.\n");
    set_adj("tower");
    set_race_name("human");
    default_config_npc(30);
    set_alignment(-50);
    set_skill(SS_WEP_POLEARM, 50);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);

    NEVERKNOWN;
}
