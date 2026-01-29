/*
 *   /d/Gondor/ithilien/poros/npcs/dunadan.c
 *
 *   This is a dunadan traveler out exploring southern ithlien.
 *
 *   Talisan,  February 1996
 */

#pragma strict_types

inherit "/std/monster";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

static void    get_money();

public void
create_monster()
{
    set_name("dunadan");
    add_name(({"traveller", "man", "adventurer"}));
    set_adj("stoic");
    add_adj("dunadan");
    set_race_name("human");
    set_long(BSN("This tall Dunadan seems to be an adventurer exploring the "
      + "region of Southern Ithilien. He looks like he is well traveled, and "
      + "appears to be quite capable of defending himself should the need arise."));

    default_config_npc(80 +random(5));

    set_base_stat(SS_STR, 90 +random(5));
    set_base_stat(SS_CON, 90 +random(5));

    set_skill(SS_WEP_SWORD, 80 +random(5));
    set_skill(SS_DEFENSE, 80 +random(5));
    set_skill(SS_PARRY, 80 +random(5));
    set_skill(SS_AWARENESS, 75 +random(5));
    set_skill(SS_BLIND_COMBAT, 75 +random(5));

    set_alignment(500);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_HEIGHT, 180 +random(30));
    add_prop(CONT_I_WEIGHT, 85000 +random(30*500));
    add_prop(CONT_I_VOLUME, 80000 +random(30 * 500));

    set_chat_time(4 +random(3));
    add_chat("I have never been to Umbar before, I think I'll travel there next.");
    add_chat("There is nothing like traveling out on the open road.");
    add_chat("If you're heading south keep an eye out for Haradrim patrols!");
    add_chat("I was almost captured by corsairs the other day!");
    add_chat("The damnable corsairs have started raiding again, so keep your eyes open.");
    add_chat("Its nice to take a rest here after a long days travel.");

    set_cchat_time(2);
    add_cchat("So be it! Death to you black one!");
    add_cchat("Your soul will soon be visiting the Halls of Mandos!");
    add_cchat("Be sure to give Mandos my regards, fiend!");
    add_cchat("Is that all the better you can do? Come back after you grow some!");

    set_act_time(4 +random(3));
    add_act("yawn");
    add_act("get all from corpse");
    add_act("get all");
    add_act("cackle");
    add_act("time");
    add_act("greet all");
    add_act("sneeze");

    set_cact_time(3);
    add_cact("shout Die, you slave of Morgoth!");
    add_cact("growl @@query_enemy_name@@");
    add_cact("glare @@query_enemy_name@@");
    add_cact("scowl @@query_enemy_name@@");
    add_cact("explode @@query_enemy_name@@");
}

public void
arm_me()
{
    seteuid(getuid());

    clone_object(POROS_DIR + "weapons/broadsword")->move(this_object());
    command("wield all");

    clone_object(POROS_DIR + "armours/chainmail")->move(this_object());
    command("wear all");

    get_money();
}

static void
get_money()
{
    MONEY_MAKE_SC(20 + random(10))->move(TO);
    MONEY_MAKE_GC(3 +random(3))->move(TO);
}

int
query_knight_prestige() {return -500;}

public string
query_enemy_name()
{
    object  enemy = query_attack();

    if (objectp(enemy))
        return enemy->query_real_name();

    return "";
}

