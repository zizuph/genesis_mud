/*
 *	/d/Gondor/common/npc/reorc.c
 *
 *	Cloned by:
 *	/d/Gondor/ithilien/forest/orcpost2.c
 *	/d/Gondor/ithilien/forest/orccamp1.c
 */
#pragma strict_types

inherit "/d/Gondor/std/monster";
inherit "/d/Gondor/common/lib/logkill.c";
inherit "/d/Gondor/common/lib/make_money.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_monster()
{
    int     rval = random(6);
    string *eq = ({ });

    set_name("orc");
    set_race_name("orc"); 
    set_adj("large");
    set_long("He is a very ugly and nasty looking orc.\n");
    default_config_npc(30 + rval);
    set_base_stat(SS_INT, 15 + rval);
    set_base_stat(SS_WIS, 15 + rval);
    set_base_stat(SS_DIS, 50 + rval / 2);

    set_alignment(-110 -random(200));

    set_skill(SS_WEP_CLUB,  35 + rval);
    set_skill(SS_WEP_SWORD, 35 + rval);
    set_skill(SS_PARRY,     15 + rval / 2);
    set_skill(SS_BLIND_COMBAT, 45 + rval);
    set_skill(SS_DEFENCE,   15 + rval);
    set_skill(SS_AWARENESS, 20 + rval * 2);
    add_prop(LIVE_I_SEE_DARK, 2);
    add_prop(CONT_I_HEIGHT,   150);
    add_prop(CONT_I_WEIGHT, 55000);
    add_prop(CONT_I_VOLUME, 60000);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_cchat("Our Master will soon rule!");
    add_cchat("The Red Eye will conquer the world!");
    add_cchat("We will feed on your dead and molested body tonight!");


    if (random(3))
    {
        eq += ({ WEP_DIR + "orcscim" });
	if (random(3))
	{
	    eq += ({ ARM_DIR + "reshield" });
	}
    }
    else
    {
	eq += ({ WEP_DIR + "orcclub" });
    }

    if (random(3))
    {
	eq += ({ ARM_DIR + "orcmail" });
	eq += ({ ARM_DIR + "rehelm" });
    }
    else if (random(2))
    {
	eq += ({ ARM_DIR + "rethelm" });
    }
    set_equipment(eq);
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

/* Solamnian Knights */
public int query_knight_prestige() { return 370; }

