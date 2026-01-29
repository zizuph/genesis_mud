/*
 * weaponsmith.c
 *
 * Used in nyreese/cadu_smith.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* The weaponsmith of Gont */
/* Coded by Glindor for use in Re-Albi */

#pragma strict_types

inherit "/std/monster";
inherit "/d/Khalakhor/lib/weapon_repairs";

#include "defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>
#include <money.h>

int has_introduced;

void
create_monster()
{
    set_name("gilahin");
    add_name("smith");
    add_name("weaponsmith");
    set_race_name("dwarf");
    set_living_name("gilahin");
    set_title("the weaponsmith");
    set_adj("strong");
    set_long("This is the weaponsmith of Cadu.\n" +
             "He looks quite torn after many years of hard work in the " +
             "blacksmith, and he's a man that commands respect.\n");
    
    set_alignment(500);

    default_config_npc(55);
    set_base_stat(SS_CON, 60);
    set_base_stat(SS_STR, 80);
    set_skill(SS_WEP_CLUB, 80);

    add_prop(OBJ_M_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_MAGIC_ATTACK, 1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
}

int query_knight_prestige(){return -3;}

void
init_living()
{
    ::init_living();
    init_smith_repairs();
}

void
equip_me()
{
    object wep;
    seteuid(getuid(this_object()));
    wep = clone_object(ROKEDIR + "wep/hammer");
    wep->move(this_object());
    command("wield hammer");
}

void
remove_int()
{
    has_introduced = 0;
}

void
add_introduced(string person)
{
    if (!has_introduced)
    {
        set_alarm(4.0, 0.0, &command("introduce myself"));
        has_introduced = 1;
        set_alarm(15.0, 0.0, remove_int);
    }
}

