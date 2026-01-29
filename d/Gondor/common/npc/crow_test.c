/*
 *	/d/Gondor/common/npc/crow.c
 *
 *	December 1995 by Olorin
 *
 *      Copyright (c) 1995, 1996 by Christian Markus
 *
 *	Modification log:
 *      18-Dec-1996, Olorin: Typo fix.
 */
#pragma strict_types

inherit "/std/creature.c";
inherit "/std/combat/unarmed.c";
inherit "/std/act/action.c";
inherit "/std/act/domove.c";

#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

public void
create_creature()
{
    set_name(({"craban", "crow", "bird", "beast", }));
    set_pname(({"crebain", "crows", "birds", }));
    set_race_name("crow");
    set_adj(({"large", "black", }));
    set_short("black crow");
    set_pshort("black crows");
    set_long(BSN("This is a large black crow or craban. These birds "
      + "live in many places in Middle Earth, in the Misty Mountains "
      + "in Fangorn and Mirkwood, and also in the mountain ranges "
      + "encircling Mordor."));
    set_alignment(0);

    set_stats(({ 5, 20, 5, 5, 5, 5 }));
    set_whimpy(80);

    set_skill(SS_AWARENESS, 90);
    set_skill(SS_DEFENCE,   40);

    add_prop(CONT_I_WEIGHT, 700);
    add_prop(CONT_I_VOLUME, 700);
    add_prop(CONT_I_MAX_WEIGHT, 800);
    add_prop(CONT_I_MAX_VOLUME, 800);

    add_prop(OBJ_M_NO_ATTACK, "@@check_attack@@");

    add_prop(LIVE_I_SEE_DARK, 5);

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " is not able to carry something.\n");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_attack_unarmed(0,  5, 15, W_IMPALE,            50, "beak");
    set_attack_unarmed(1, 15, 10, W_SLASH | W_IMPALE,  75, "claws");

    set_hitloc_unarmed(0, ({ 12, 12,  5}),  40, "body");
    set_hitloc_unarmed(1, ({ 15,  5, 15}),  20, "left wing");
    set_hitloc_unarmed(2, ({ 15,  5, 15}),  20, "right wing");
    set_hitloc_unarmed(3, ({ 20, 10,  5}),  10, "head");
    set_hitloc_unarmed(4, ({ 10, 10, 20}),  10, "claws");

    set_act_time(10);
    add_act("emote croaks harshly.");
    add_act("emote croaks threateningly.");
    add_act("emote croaks dangerously.");
    add_act("emote flaps its wings.");
    add_act("peer");

    set_alarm(0.0, 0.0, &set_m_in("flies into view"));
    set_alarm(0.0, 0.0, &set_m_out("flies away to the"));
}

mixed
check_attack()
{
    int     seed,
            dummy;

    sscanf(OB_NUM(TO), "%d", dummy);
    seed = dummy;
    sscanf(OB_NUM(TP), "%d", dummy);
    seed += dummy;

    if (random(5, seed))
        return "The "+short()+" is flying out of reach. It is "
             + "impossible to attack it.\n";
    return 0;
}

