/*
 *	/d/Gondor/common/ship/gsl_captain.c
 *
 *	The generic ship captain for Gondor.
 *
 *	Copyright (c) 1997 by Christian Markus
 *
 *	Coded by Olorin, February 1997
 *
 *	Modification log:
 *  Adapted to new ship code by Tapakah
 */
#pragma save_binary
#pragma strict_types

#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"

#define CUTLASS "/d/Gondor/common/ship/cutlass"
#define FIX_EUID   { setuid(); seteuid(getuid()); }

inherit STDCAPTAIN;

static object  Ship;
static string  Target,
               Harbour;

static void
create_gondor_captain()
{
    ::create_monster();
}

public nomask void
create_captain()
{
  ::create_captain();
  set_name("captain");

    // Default values:
    default_config_npc(60);
    set_base_stat(SS_STR, 80);
    set_base_stat(SS_CON, 80);

    set_skill(SS_SWIM,         100);
    set_skill(SS_LOC_SENSE,    100);
    set_skill(SS_WEP_SWORD,    100);
    set_skill(SS_UNARM_COMBAT,  80);
    set_skill(SS_DEFENCE,       50);
    set_skill(SS_PARRY,         50);
    set_skill(SS_BLIND_COMBAT,  90);
    set_skill(SS_AWARENESS,     90);

    set_alignment( 500);

    add_prop(CONT_I_HEIGHT,   190);
    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_VOLUME, 69000);

    create_gondor_captain();

    add_ask( ({ "lord", "carastur", "councillor", }), 
	    QCTNAME(TO) + " says: Carastur is the Lord Councillor of "
	    + "Pelargir.\n" +
	    QCTNAME(TO) + " says: You can find him in the cityhall.\n");
    add_ask( ({ "master", "master of advice", "hunthor", }), 
	    QCTNAME(TO) + " says: Hunthor is the Master of Advice in "
	    + "Minas Tirith.\n" + 
	    QCTNAME(TO) + " says: You can find him in the Administration "
	    + "Office in the Third Circle of the city.\n");
    set_default_answer(VBFC_ME("default_answer"));
}

/*
 * Function name:   second_life
 * Description:     Handles all that should happen when a captain dies.
 * Argument:        Object that caused the kill.
 * Returns:         True if the living object should get a second life
 */
public int
second_life(object killer)
{
    ::second_life();

    FIX_EUID;
    log_file("captain", killer->query_name() + " killed " + 
	     query_name() + " on " + ctime(time()) + ".\n");
    return 0;
}

public void
arm_me()
{
    FIX_EUID;
    clone_object(CUTLASS)->move(TO);

    command("wield cutlass");
}

public void
introduce_me(object tp)
{
    if (objectp(tp) && objectp(present(tp, ENVX(TO))))
        command("introduce me to " + tp->query_real_name());
}

void
add_introduced(string str)
{
    object  tp;

    if (objectp(tp = find_player(str)) && 
	!tp->query_met(query_name()))
	set_alarm(2.0, 0.0, &introduce_me(tp));
}

/* 
 * Solamnian knights prestige 
 */
public int 
query_knight_prestige() 
{
    return -15;
}

string 
default_answer()
{
    command("say I don't know what you are talking about, "+TP->query_race_name()+"!");
    command("say Perhaps you want to know, where we are sailing?");
    command("peer " + TP->query_real_name());
    command("say Then ask me about the destination!");
    return "";
}
