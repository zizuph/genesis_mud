/*
 * towerg4.c
 *
 * Used in nyreese/cas_t41.c nyreese/cas_t42.c
 * Used in nyreese/cas_t43.c nyreese/cas_t44.c
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
    clone_object(ROKEDIR + "wep/steelsword")->move(TO);
    clone_object(ROKEDIR + "arm/lboots")->move(TO);
    clone_object(ROKEDIR + "arm/steelhelmet")->move(TO);
    clone_object(ROKEDIR + "arm/steelmail")->move(TO);

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
    default_config_npc(90);
    set_alignment(-500);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 75);

    NEVERKNOWN;
}
