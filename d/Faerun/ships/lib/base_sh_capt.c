/*
 *	The generic ship captain for Gondor.
 *	Copyright (c) 1997 by Christian Markus
 *	Coded by Olorin, February 1997
 *  -- Modified for Faerie by Finwe, January 2006
 *	Modification log:
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/captain.c";

#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Faerun/defs.h"
#include "defs.h"

#define MIN_STAT_TICKET		20

static object  Ship;
static string  Target,
               Harbour;

static void   set_target(string s)  { Target  = s; }
static void   set_harbour(string s) { Harbour = s; }

static void
create_faerie_captain()
{
}

public nomask void
create_captain()
{
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

    create_faerie_captain();

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

    setuid();
    seteuid(getuid());

    log_file("captain", killer->query_name() + " killed " + 
	     query_name() + " on " + ctime(time()) + ".\n");
    if (objectp(Ship))
	Ship->stop_ship("The ship stops; Someone killed the captain!\n");
    return 0;
}

/*
 * Function name: set_ship
 * Description:   Set our ship.
 */
public void
set_ship(object s)
{
    Ship = s;
}

public void
arm_me()
{
    setuid();
    seteuid(getuid());
/*
    clone_object(WEP_DIR + "longsword")->move(TO);
    command("wield weapon");
*/
}

/*
 * Function name: do_buy
 * Description:   Do not sell tickets to those who travel for free.
 * Argument:      str - command line arg
 * Returns:       1/0
 */
 
public int
buy(string str)
{
    if (TP->query_average_stat() < MIN_STAT_TICKET)
    {
        command("say You don't need to buy any ticket.");
        command("smile "+TP->query_real_name());
        command("say Young travel for free.");
        return 1;
    }

    return ::buy(str);
}

public void
introduce_me(object tp)
{
    if (objectp(tp) && objectp(present(tp, ENV(TO))))
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
