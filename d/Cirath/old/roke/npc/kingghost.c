/*
 * kingghost.c
 *
 * Used in carisca/d3.c
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
    default_config_npc(100);

    set_race_name("ghost");
    set_name("ghost");
    add_name("king");

    add_prop(LIVE_I_UNDEAD, 75);

    set_short("ghost of dwarf king");

    set_long("This is the ghost of the former dwarf king, haunting the " +
             "mountain to protect his treasury.\n");
    set_alignment(30);


    set_skill(SS_UNARM_COMBAT, 25);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 75);

    set_skill(SS_WEP_AXE, 100);
}

int
query_knight_prestige()
{
    return -1;
}

void
do_die(object killer)
{
    if (query_hp() > 0)
        return;

    query_combat_object()->cb_death_occured(killer);

    killer->notify_you_killed_me(this_object());
    command("drop all");
    tell_room(E(TO), "The ghost dissolves in a strange mist.\n");
    remove_object();
}

void
equip_me()
{
    clone_object(ROKEDIR + "wep/kingaxe")->move(TO);
    clone_object(ROKEDIR + "arm/kingmail")->move(TO);
    clone_object(ROKEDIR + "arm/kinghelm")->move(TO);
    clone_object(ROKEDIR + "arm/kinggaunt")->move(TO);

    command("wear all");
    command("wield all");
}
