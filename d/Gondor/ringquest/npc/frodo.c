/*
 *	/d/Gondor/ringquest/npc/frodo.c
 *
 *	Copyright (C) 1995 by Christian Markus
 *
 *	Mr Frodo Baggins of Bag End, Hobbiton.
 *
 *	Olorin, December 1995
 *
 *	Modification log:
 */
#pragma strict_types

inherit "/d/Gondor/ringquest/npc/rq_npc.c";

#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/ringquest/lib/defs.h"

#define SUBLOC_LEG_BROKEN	"_subloc_leg_broken"

public void
create_rq_npc()
{
    set_living_name("frodo");
    set_name( ({"frodo", "baggins", }) );
    set_title("son of Drogo");
    set_race_name("hobbit");

    set_adj( ({"energetic", "friendly", }) );

    set_stats( ({ 40, 70, 60, 70, 100, 75, }) );
    set_exp_factor(50);

    set_skill(SS_WEP_SWORD, 50);
    set_skill(SS_DEFENCE,   30);
    set_skill(SS_PARRY,     20);
    set_skill(SS_LANGUAGE,  90);
    set_skill(SS_AWARENESS, 70);
    set_skill(SS_SNEAK,     80);
    set_skill(SS_HIDE,      80);
}

public int
do_break_leg()
{
    // Cannot break his leg if it's already broken.
    if (stringp(show_cont_subloc(SUBLOC_LEG_BROKEN, TO)))
        return 0;

    add_subloc(SUBLOC_LEG_BROKEN, TO);
    return 1;
}

/*
public string
show_subloc(string subloc, object me, object for_obj)
{
    string  str,
            other = "";

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (subloc != SUBLOC_LEG_BROKEN)
        return TO->show_subloc(subloc, me, for_obj);

    if (for_obj == me)
        str = "Your";
    else
    {
        str = CAP(HIS(TO));
        other = "The leg must be broken.\n"
              + "It seems obvious that this hobbit will not be able "
              + "walk for several weeks.\n";
    }

    str += " right leg has been put in splints reaching from the "
        +  "foot up to the hip.\n" + other;

    return str;
}
*/
