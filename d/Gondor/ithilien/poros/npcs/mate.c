/*
 *   /d/Gondor/ithilien/poros/npcs/mate.c
 *
 *   This is the first mate of the pirate crew.
 *
 *   Talisan,  February 1996
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/poros/npcs/corsair_master";

#include <stdproperties.h>
#include <composite.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

public void
create_corsair()
{
    set_name("corsair lieutenant");
    add_name(({"pirate", "woman", "mate", "lieutenant", "corsair"}));
    remove_name("man");
    set_adj(({"cold-blooded", "corsair"}));
    set_gender(G_FEMALE);
    set_long(BSN("This pure blooded, long-haired Corsair is a very dangerous looking woman. "
      + "A lieutenant of the pirate crew, she has gained her position by skill in arms, and by "
      + "leadership of a cold-blooded, fierce nature."));

    default_config_npc(90+random(5));
    set_base_stat(SS_DEX, 115+random(5));
    set_base_stat(SS_STR, 105+random(5));
    set_base_stat(SS_DIS, 95+random(5));
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_PARRY, 80+random(10));
    set_skill(SS_DEFENCE, 80+random(10));
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_AWARENESS, 80+random(15));

    set_alignment(-150);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_HEIGHT, 185 +random(30));
    add_prop(CONT_I_WEIGHT, 65000 +random(30*500));
    add_prop(CONT_I_VOLUME, 60000 +random(30*500));

    set_chat_time(4 +random(3));
    add_chat("Let's look sharp boys, no loafing on my watch.");
    add_chat("If anybody has a problem with their orders, too bad.");
    add_chat("Don't let the Captain hear you saying that.");
    add_chat("We'll be back on the Anduin plundering before you know it!");
    add_chat("I hope the other crew returns soon.");
    add_chat("I can't wait to command the Drake!");
    add_chat("Someone kill the cook, this stew is inedible!");
    add_chat("I think Umbar and Minas Morgul should join against Gondor.");


    set_cchat_time(2 +random(2));
    add_cchat("Die, you rancid dog!");
    add_cchat("Your head will soon be on a pole!");
    add_cchat("Looks like we have another slave!");
    add_cchat("For Umbar!");
    add_cchat("Death to Gondor!");
    add_cchat("Long live the Corsairs!");
    add_cchat("Castamir Lives!");

}

public void
arm_me()
{
    clone_object(POROS_DIR + "armours/plated_leather")->move(this_object());
    clone_object(POROS_DIR + "armours/helmet")->move(this_object());
    command("wear all");

    clone_object(UNIQUE_CLONE(POROS_DIR + "weapons/black_dagger", 5,
	WEP_DIR + "stiletto"))->move(this_object());
    clone_object(POROS_DIR + "weapons/silver_sword")->move(this_object());
    command("wield all");

    get_money();
}

void
get_money()
{
    MONEY_MAKE_SC(10 + random(10))->move(TO);
    MONEY_MAKE_GC( 5 + random( 5))->move(TO);
}

int
query_knight_prestige() {return 150;}
