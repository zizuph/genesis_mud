/*
 * campleader.c
 *
 * Used in wild/tent.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <macros.h>
#include <ss_types.h>

void
create_monster()
{
    set_name("leader");
    add_name("warrior");
    set_short("warrior leader");
    set_adj("warrior");
    add_name("human");

    NEVERKNOWN;

    set_long("This is the leader of the warriors from Golbar. " +
             "You don't think you'd like to fight with him.\n");

    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_WEP_AXE, 100);

    set_alignment(-50);

    default_config_npc(80);

    add_notify_meet_interactive("meet");
}

int
query_knight_prestige()
{
    return 900;
}

void
equip_me()
{
    clone_object(ROKEDIR + "wep/battleaxe3")->move(TO);
    clone_object(ROKEDIR + "arm/doublemail")->move(TO);
    clone_object(ROKEDIR + "arm/doublehelmet")->move(TO);

    command("wield all");
    command("wear all");
}

void
curse()
{
    command("growl");
    command("say What are you doing here???");
    command("emote polishes his axe.");
}

void
meet()
{
    set_alarm(1.0, 0.0, curse);
}
