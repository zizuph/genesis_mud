/*
 
 ~shire/common/ship/riondir.c

 by Palmer 
 Based heavily on Gondor's captains:
  1997 by Christian Markus
 	Coded by Olorin, February 1997
 ChangeLog:
 
 
*/
#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/captain.c";

#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#define MIN_STAT_TICKET		20

static object  Ship;
static string  Target,
               Harbour;

static void   set_target(string s)  { Target  = s; }
static void   set_harbour(string s) { Harbour = s; }


public nomask void
create_captain()
{
    set_name(({"riondir", "captain"}));
    set_title("Captain of the Flying Swan");
    set_living_name("_riondir_");
    set_race_name("elf");
    add_adj("tall");

    add_prop(OBJ_M_NO_ATTACK, "Trust me, you don't want to attack this long-time seafarer.\n");

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

