/*
 * towerg2.c
 *
 * Used in nyreese/cas_t21.c nyreese/cas_t22.c
 * Used in nyreese/cas_t23.c nyreese/cas_t24.c
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
equip_me()
{
    clone_object(ROKEDIR + "wep/spear")->move(TO);
    clone_object(ROKEDIR + "arm/lboots")->move(TO);
    clone_object(ROKEDIR + "arm/chelmet")->move(TO);
    if (random(8))
    {
        clone_object(ROKEDIR + "arm/cpmail")->move(TO);
    }
    else
    {
        clone_object(ROKEDIR + "arm/steelmail")->move(TO);
    }

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
    default_config_npc(50);
    set_alignment(200);
    set_skill(SS_WEP_POLEARM, 50);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);

    NEVERKNOWN;
}
