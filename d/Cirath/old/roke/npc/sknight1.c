/*
 * sknight1.c
 *
 * Used in nyreese/cas_a3.c
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
    clone_object(ROKEDIR + "wep/sword")->move(TO);
    clone_object(ROKEDIR + "arm/brigandine")->move(TO);
    clone_object(ROKEDIR + "arm/chainhelm")->move(TO);
    clone_object(ROKEDIR + "arm/lboots")->move(TO);

    command("wear all");
    command("wield all");
}

void
create_monster()
{
    set_name("knight");
    add_name("guard");

    set_adj("strong");
    set_race_name("human");
    set_short("strong knight");
    set_long("The knight guards the stairs and stops anyone that " +
             "wants to go to the next floor.\n");

    default_config_npc(35);
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_WEP_SWORD, 40);

    set_alignment(30);
    NEVERKNOWN;
}
