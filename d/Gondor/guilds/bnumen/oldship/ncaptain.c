/*
 *	
 *	Modification log:
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/captain.c";

#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MIN_STAT_TICKET  20

static object  Ship;
static string  Target,
               Harbour;

static void   set_target(string s)  { Target  = s; }
static void   set_harbour(string s) { Harbour = s; }


public nomask void
create_captain()
{

    set_name("beltharzor");
    add_name("captain");
    // Default values:
    default_config_npc(200);
    set_base_stat(SS_STR, 200);
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

public void
arm_me()
{
    FIX_EUID;
    clone_object(SHIP_DIR + "cutlass")->move(TO);

    command("wield cutlass");
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
    // add some other checks?
    command("say You don't need a ticket! This is no merchant " +
        "trader! You must be a true Numenorean to board here.");
    return 1;
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

public void
catch_question(string question)
{
    int      i,
             loc,
             length;
    string   str;

    if (dont_answer_unseen && (!TP->check_seen(TO) ||
        !CAN_SEE_IN_ROOM(TO)))
    {
        set_alarm(itof(random(3) + 1), 0.0, unseen_hook);
	return;
    }

    i = strlen(question);
    if (question[i - 1] == "."[0] || question[i - 1] == "?"[0])
	question = extract(question, 0, i - 2);

    posed_question = lower_case(question);

    str = explode(posed_question," ")[0];
    if (str != "where" && str != "destination")
        ::catch_question(question);
    else if(!objectp(Ship))
        set_alarm(rnd() * 4.0, 0.0, &command("say I'm not going anywhere!"));
    else if((loc = Ship->query_location()) == 0)
        set_alarm(rnd() * 4.0, 0.0, &command("say We will sail to " + 
					     CAP(Target) + " shortly."));
    else if (loc < (length = sizeof(Ship->query_places_to_go())) /2 )
        set_alarm(rnd() * 4.0, 0.0, &command("say We are on our way to " + 
					     CAP(Target) + "!"));
    else if (loc == length/2)
        set_alarm(rnd() * 4.0, 0.0, &command("say We will sail to " +
					     CAP(Harbour) + " shortly!"));
    else
        set_alarm(rnd()*4.0, 0.0, &command("say We are on our way to " +
					   CAP(Harbour) + "!"));

    return;
}

string 
default_answer()
{
    command("say I don't know what you are talking about, "+TP->query_race_name()+"!");
    command("say Perhaps you want to know, where we are sailing?");
    command("peer " + TP->query_real_name());
    command("say Then ask me, 'where are we sailing'!");
    return "";
}

/*
 * Function name: init_living
 * Description:   The normal init_living
 */
void
init_living()
{
    ::init_living();
    
    add_action(buy, "buy");
}