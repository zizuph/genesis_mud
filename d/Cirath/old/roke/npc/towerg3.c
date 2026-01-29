/*
 * towerg3.c
 *
 * Used in nyreese/cas_t31.c nyreese/cas_t32.c
 * Used in nyreese/cas_t33.c nyreese/cas_t34.c
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
    if (random(5))
    {
        clone_object(ROKEDIR + "wep/spear")->move(TO);
    }
    else
    {
        clone_object(ROKEDIR + "wep/steelsword")->move(TO);
    }
    clone_object(ROKEDIR + "arm/lboots")->move(TO);
    if (random(5))
    {
        clone_object(ROKEDIR + "arm/chelmet")->move(TO);
    }
    else
    {
        clone_object(ROKEDIR + "arm/steelhelmet")->move(TO);
    }
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
    default_config_npc(70);

    set_skill(SS_WEP_POLEARM, 70);
    set_skill(SS_WEP_SWORD, 70);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_PARRY, 70);
    set_alignment(350);

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    NEVERKNOWN;
}
