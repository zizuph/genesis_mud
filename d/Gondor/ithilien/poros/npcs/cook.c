/*
 *   /d/Gondor/ithilien/poros/npcs/cook.c
 *
 *   This is the cook of the corsairs.
 *
 *   Talisan,  February 1996
 */

#pragma strict_types

inherit "/std/monster";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>

#include "/d/Gondor/defs.h"

//      Prototypes
void    get_money();

public void
create_monster()
{
    seteuid(getuid(TO));

    set_name("corsair cook");
    add_name(({"corsair", "cook", "pirate", "umbarian"}));
    add_name("_poros_corsair");
    set_adj("fat");
    add_adj("umbarian");
    set_race_name("human");
    set_long(BSN("This is an extremly fat and ugly human. His clothes are "
      + "dirty and stained with food. You gather from his overall "
      + "appearance the he is the cook for the corsairs based here in "
      + "the manor. You decide the only thing dangerous about this man "
      + "is his awful smell."));

    default_config_npc(40 +random(5));

    set_skill(SS_DEFENSE, 25 +random(5));
    set_skill(SS_PARRY, 25 +random(5));
    set_skill(SS_UNARM_COMBAT, 35 +random(5));

    set_alignment(-50);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_HEIGHT, 160 +random(10));
    add_prop(CONT_I_WEIGHT, 95000 +random(30*500));
    add_prop(CONT_I_VOLUME, 90000 +random(30*500));

    set_chat_time(3 +random(3));
    add_chat("Have you talked to the Captain yet? He needs someone to help him with a task.");
    add_chat("It's always do this, do that, never a break!");
    add_chat("Want to try some of my carp stew?");
    add_chat("Damn it all, this kitchen is always a mess!");
    add_chat("That blasted fire is always going out...");
    add_chat("I should have signed on with the Haradrim army...");
    add_chat("I hate being cooped up in this place.");

    set_cchat_time(3);
    add_cchat("Why would want to attack me?");
    add_cchat("I'm not the weakling you think I am!");
    add_cchat("I REALLY should have signed on with the Haradrim army...");
    add_cchat("If you kill me the others will hunt you down!");
    add_cchat("Please, oh please have mercy on me!");

    set_act_time(5 +random(5));
    add_act("emote takes a good look into the kettle.");
    add_act("sigh");
    add_act("emote cleans up the table.");
    add_act("emote peers out into the dining hall.");
    add_act("burp");
    add_act("emote picks his nose.");
    add_act("emote begins to clean some utensils.");
    add_act("emote pulls down a pot off the wall.");

    set_cact_time(4 +random(3));
    add_cact("scream");
    add_cact("shout Help! I'm being attacked in here!");
    add_cact("tremble");
    add_cact("cry");
    add_cact("cower");
    add_cact("emote starts running around the table trying to get away.");

}

public void
arm_me()
{
    clone_object(POROS_DIR + "armours/leather")->move(this_object());
    command("wear all");

    get_money();
}

void
get_money()
{
    MONEY_MAKE_CC(30 +random(20))->move(TO);
    MONEY_MAKE_SC(3 +random(3))->move(TO);
}
