/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "defs.h"

void
create_monster()
{
    int i;
    string name;

    set_race_name("dwarf");

    set_random_move(15);
    set_act_time(20);
    add_act("puke");
    add_act("smile");
    add_act("giggle");
    add_act("scream");

    add_ask("scream","There is something crawling around in the forest! Ants! Ants! Take them away from me!\n");

    i = random(2); /* select a random gender */

    set_gender(i);

    if(i)
    {
        switch(random(6))
        {
        case 0: name = "anna"; break;
        case 1: name = "maria"; break;
        case 2: name = "lisa"; break;
        case 3: name = "brenda"; break;
        case 4: name = "kelly"; break; /* guess I've watched beverly hills too much :) */
        case 5: name = "jeanette"; break;
        }
    }
    else
    {
        switch(random(6))
        {
        case 0: name = "john"; break;
        case 1: name = "jack"; break;
        case 2: name = "hank"; break;
        case 3: name = "richard"; break;
        case 4: name = "woody"; break;
        case 5: name = "peter"; break;
        }
    }

    set_name(name);

    name = "small";

    switch(random(5))
    {
    case 0: name = "tall"; break;
    case 1: name = "skinny"; break;
    case 2: name = "young"; break;
    case 4: name = "fat"; break;
    case 5: name = "stupid"; break;
    }

    set_adj(name);

    switch(random(5))
    {
    case 0: name = "is walking around, restlessly.\n"; break;
    case 1: name = "looks at you, with curious eyes.\n"; break;
    case 2: name = "seems rather tired.\n"; break;
    case 3: name = "jumps up and down, singing a merry tune.\n"; break;
    case 4: name = "is dressed rather fancy.\n"; break;
    case 5: name = "smells awfully.\n"; break;
    }

    set_long((i?"She":"He")+" "+name);

    default_config_npc(15+random(35));

    set_skill(SS_UNARM_COMBAT,5+random(5));
    set_skill(SS_DEFENCE,5+random(5));
    set_skill(SS_WEP_AXE,10+random(10));
}

void
arm_me()
{
    int i;
    object axe,armour;

    i = query_average_stat() / 10;

    axe  = clone_object(S_LOCAL_WEP_DIR+"randomaxe");
    axe->configaxe(i);

    armour = clone_object(S_LOCAL_ARM_DIR+"randomarmour");
    armour->configarmour(i);

    axe->move(TO);
    armour->move(TO);

    command("wear all");
    command("wield all");
}

