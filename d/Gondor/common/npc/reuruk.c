/*
 *	/d/Gondor/common/npc/reuruk.c
 *
 *	Cloned by:
 *	/d/Gondor/ithilien/forest/orccamp1.c
 *	/d/Gondor/ithilien/forest/orcpost2.c
 *	/d/Gondor/ithilien/forest/orctent1.c
 *	/d/Gondor/ithilien/forest/orctent3.c
 *
 *  21-10-2000 Stern, Modified to autoattack good aligned folks.
 */
#pragma strict_types

inherit "/d/Gondor/std/monster.c";
inherit "/d/Gondor/common/lib/logkill.c";
inherit "/d/Gondor/common/lib/make_money.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_gondor_monster()
{
    set_name("uruk");
    set_race_name("orc"); 
    set_adj( ({ "muscular", "ugly", }) );
    set_long("He is a very ugly and muscular uruk commander.\n");
    default_config_npc(43+random(6));
    set_base_stat(SS_DEX, 45);
    set_base_stat(SS_CON,45);
    set_alignment(-210-random(200));
    set_skill(SS_WEP_CLUB,random(35)+35);
    set_skill(SS_WEP_SWORD,35+random(35));
    set_skill(SS_PARRY,random(30)+30);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_DEFENCE,random(30)+30);
    set_skill(SS_AWARENESS,random(30)+30);
    add_prop(CONT_I_HEIGHT,150);
    add_prop(CONT_I_WEIGHT, 65000);
    add_prop(CONT_I_VOLUME, 65000);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_cchat("The Eye will soon rule!");
    add_cchat("The Red Eye is going to dominate the world!");
    add_cchat("We will feed on your dead and molested body tonight!");
    add_cchat("I am a fighting Uruk! Men of Gondor don't scare me!");

    if (random(2))
    {
    	set_equipment( ({ (WEP_DIR + "uruksword"), (ARM_DIR + "orcmail"),
	    (ARM_DIR + "rehelm") }) );
    }
    else
    {
    	set_equipment( ({ (WEP_DIR + "uruksword"), (ARM_DIR + "orcmail"),
	    (ARM_DIR + "rethelm") }) );
    }
}

public void
init_attack()
{
    object  victim;

    if (objectp(query_attack()))
        return;

    if ((victim = TP)->query_npc())
        return;
    if (!IS_GOOD(victim) || !CAN_SEE(TO, victim))
        return;

    set_alarm(0.0, 0.0, &command("kill " + victim->query_real_name()));
}



public void
arm_me()
{
    ::arm_me();
    get_money();
}



/* solemnians */
public int query_knight_prestige() { return 500; }
