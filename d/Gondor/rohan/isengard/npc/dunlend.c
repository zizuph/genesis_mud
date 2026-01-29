/*
 * /d/Gondor/rohan/isengard/npc/dunlend.c
 *
 * Original version by unknown.
 * 
 * This version:
 * Copyright (c) 1996 by Christian Markus
 *
 * Modification log:
 *  3-Dec-1996, Olorin: general revision
 * 29-Jan-1997, Olorin: Another try to fix the corpse plural 'mans'.
 */
#pragma strict_types

inherit "/d/Gondor/rohan/isengard/npc/team.c";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

public void
create_monster() 
{
    default_config_npc( 55 + random(11));
    set_base_stat(SS_CON, 75);
    set_base_stat(SS_INT, 65 + random(11));
    set_base_stat(SS_WIS, 61 + random(15));
    set_race_name("human"); 
    set_name( ({ "guard", "man", "dunlending", }) );
    set_adj( ({ "tall", "dark-haired", "swarthy", }) );
    set_pshort("dark-haired men, guarding the gate");
    set_long("The dunlendings are fearsome warriors, and this one is "+
    "no exception. He is tall, swarthy and dark haired.\n");
    set_alignment( -100 - random(101));
    set_attack_chance(90);
    set_skill(SS_WEP_POLEARM, 60 + random( 6));
    set_skill(SS_DEFENCE,     30 + random( 6));
    set_skill(SS_PARRY,       30 + random( 6));
    set_skill(SS_AWARENESS,   60 + random(16));
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_S_EXTRA_SHORT, ", guarding the gate");
}

public void
arm_me()
{
    FIX_EUID 

    clone_object(ISEN_DIR+"wep/poleaxe")->move(TO);
    clone_object(ISEN_DIR+"arm/brigandine")->move(TO);
    clone_object(ISEN_DIR + "arm/whhelm")->move(TO);

    command("wield all");
    command("wear all");

    MONEY_MAKE_CC(25 + random(41))->move(TO);
    MONEY_MAKE_SC( 5 + random(11))->move(TO);
}

public void
leave_env(object inv, object to)
{
    ::leave_env(inv, to);

    if (inv->query_is_gate())
    {
	remove_prop(LIVE_S_EXTRA_SHORT);
        set_pshort("dark-haired men");
    }
    if (to->query_is_gate())
    {
	add_prop(LIVE_S_EXTRA_SHORT, ", guarding the gate");
        set_pshort("dark-haired men, guarding the gate");
    }
}

