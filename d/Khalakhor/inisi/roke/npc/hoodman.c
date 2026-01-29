/*
 * hoodman.c
 *
 * Used in wild/f9.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <ss_types.h>
#include <macros.h>

void
create_monster()
{
    int i;

    set_name("human");
    add_name("furnak");
    set_short("hooded human");
    set_long("He looks like a man who likes to walk around in the forest.\n");
    set_adj("hooded");
    set_race_name("human");
    NEVERKNOWN;

    set_skill(SS_DEFENCE, 40);
    set_skill(SS_WEP_POLEARM, 35);
    set_skill(SS_UNARM_COMBAT, 40);

    default_config_npc(25);

    set_random_move(60);
    set_restrain_path(WILDDIR + "f");

    set_alignment(400);

    ::create_monster();
}

void
equip_me()
{
    clone_object(ROKEDIR + "wep/oaklog")->move(TO);
    clone_object(ROKEDIR + "arm/cloak2")->move(TO);

    command("wear all");
    command("wield all");
}
