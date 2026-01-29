/*
 *	/d/Gondor/common/npc/reorc2.c
 *
 *	Cloned by:
 */
#pragma strict_types

inherit "/d/Gondor/std/monster.c";
inherit "/d/Gondor/common/lib/logkill.c";
inherit "/d/Gondor/common/lib/make_money.c";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_gondor_monster()
{
    string *eq = ({ });

    set_name("orc");
    set_race_name("orc"); 
    set_adj("large");
    set_long("He is a very ugly and nasty looking orc.\n");
    default_config_npc(22+random(6));
    set_base_stat(SS_DEX, 35);
    set_base_stat(SS_CON, 35);
    set_alignment(-110 -random(100));
    set_skill(SS_WEP_CLUB,  35 + random(15));
    set_skill(SS_WEP_SWORD, 35 + random(15));
    set_skill(SS_PARRY,     15 + random(25));
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_DEFENCE,   15 + random(20));
    set_skill(SS_AWARENESS, 20 + random(20));
    add_prop(LIVE_I_SEE_DARK, 2);
    add_prop(CONT_I_HEIGHT, 150);
    add_prop(CONT_I_WEIGHT, 45000);
    add_prop(CONT_I_VOLUME, 60000);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_cchat("Our Master will soon rule!");
    add_cchat("The Red Eye will conquer the world!");
    add_cchat("We will feed on your dead and molested body tonight!");

    if (random(3))
    {
	eq += ({ WEP_DIR + "orcscim" });
	if (random(2))
	    eq += ({ ARM_DIR + "reshield" });
    }
    else
	eq += ({ WEP_DIR + "orcclub" });
    if (random(2))
	eq += ({ ARM_DIR + "orcmail" });
    if (random(3))
	eq += ({ ARM_DIR + "rehelm" });
}

public void
init_attack()
{
    object  victim;

    if (objectp(query_attack()))
        return;

    if ((victim = TP)->query_npc())
        return;
    if (!IS_GOOD(victim))
        return;

    set_alarm(0.0, 0.0, &command("kill " + victim->query_real_name()));
}

public void
arm_me()
{
    ::arm_me();
    get_money();
}

/* solemnian knights */
public int query_knight_prestige() { return 350; }

