/*
 *   /d/Gondor/ithilien/poros/npcs/guard.c
 *
 *   This is a bodyguard to the corsair captain.
 *
 *   Talisan,  March 1996
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

int
special_attack(object victim)
{
    int i;

    i = random(10);

    if (!sizeof(TO->query_weapon(-1)))
        command("wield weapon");
    if (!i == 0 )
        return 0;

    victim->add_attack_delay(10 + random(11));
    TO->catch_msg("You kick your enemy in the stomach, leaving "
          + OBJECTIVE(victim) + " breathless.\n");
    victim->catch_msg(QCTNAME(TO) + " kicks you in the stomach leaving you "
          + "breathless.\n");
    say(QCTNAME(TO) + " kicks " + QTNAME(victim) + " in the stomach "
          + "leaving " + OBJECTIVE(victim) + " breathless.\n", victim);

    command("close door");
    return 0;
}


public void
create_corsair()
{
    set_name("corsair guard");
    add_name(({"pirate", "guard", "bodyguard", "corsair"}));
    set_adj(({"muscular", "corsair"}));
    set_long(BSN("This tall, muscular looking corsair seems to be "
      + "watching your every move. From his vigilant manner, he "
      + "appears to be a bodyguard for the Captain of the corsairs. "
      + "He is likely a capable opponent in combat."));

    default_config_npc(80+random(5));
    set_base_stat(SS_DEX, 95+random(5));
    set_base_stat(SS_DIS, 95+random(5));
    set_skill(SS_WEP_SWORD, 85+random(5));
    set_skill(SS_PARRY, 80+random(10));
    set_skill(SS_DEFENCE, 80+random(10));
    set_skill(SS_2H_COMBAT, 75+random(10));
    set_skill(SS_AWARENESS, 70+random(15));
    set_skill(SS_UNARM_COMBAT, 90+random(10));

    set_alignment(-75);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_HEIGHT, 170 +random(30));
    add_prop(CONT_I_WEIGHT, 75000 +random(30*500));
    add_prop(CONT_I_VOLUME, 70000 +random(30*500));


    set_cchat_time(4 +random(4));
    add_cchat("Die, you rancid dog!");
    add_cchat("Your head will soon be on a pole!");
    add_cchat("Looks like we have another slave!");
    add_cchat("For Umbar!");
    add_cchat("Death to Gondor!");
    add_cchat("Long live the Corsairs!");
    add_cchat("Castamir Lives!");
    add_cchat("You dare attack a corsair?");
    add_cchat("You will pay for you're mistake!");
  
}

public void
arm_me()
{
    clone_object(POROS_DIR + "weapons/cutlass")->move(this_object());
    clone_object(POROS_DIR + "weapons/cutlass")->move(this_object());
    command("wield all");

    clone_object(POROS_DIR + "armours/plated_leather")->move(this_object());
    clone_object(POROS_DIR + "armours/helmet")->move(this_object());
    command("wear all");

    get_money();
}

void
get_money()
{
    MONEY_MAKE_GC(1 + random(10))->move(TO);
    MONEY_MAKE_SC( 20 + random( 10))->move(TO);
}

int
query_knight_prestige() {return 75;}
