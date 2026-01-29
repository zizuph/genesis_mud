/*
 * SLEEPOBJ.c
 * This object contains a counter which reflects the number of exits
 * a player has been through in the forest. A function is called to increase
 * this number, and, once it reaches a certain threshold, the player falls
 * asleep and will wake up to find themselves outside the forest.
 * - Alaron Nov 28, 1997
 */

#include "/d/Emerald/defs.h"
#include "../coramar.h"
#include "../dirheader.h"

inherit "/std/object";

private int sleep_counter;

public void add_sleep(int incval);
public void do_player_sleep();
public void stop_paralyze();

void
create_object()
{
    set_name("_coramar_sleep_ob_");
    set_no_show();

    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);

    add_prop(OBJ_M_NO_DROP, "Drop What?\n");
    add_prop(OBJ_M_NO_GIVE, "Give What?\n");
    add_prop(OBJ_I_VALUE, 0);
}

public void
add_sleep(int incval)
{
    sleep_counter+=incval;

    if (sleep_counter > ((environment(this_object())->query_base_stat(SS_CON))/2))
        do_player_sleep();
}

public void
do_player_sleep()
{
    object paralyze_ob;

    reset_euid();
    environment(this_object())->catch_msg("You suddenly feel an overwhelming need to close your "+
	"eyes and sleep .... \n\n"+
	"You drop to your knees and feel the warm embrace of sleep before you even "+
	"notice your head hitting the damp forest floor.\n\n");
    tell_room(environment(environment(this_object())),
	QCTNAME(environment(this_object()))+" suddenly drops to "+
	environment(this_object())->query_possessive()+
 	" knees and is snoring before "+
	environment(this_object())->query_possessive()+" head "+
	"hits the damp forest floor.\n", environment(this_object()));
    environment(this_object())->command("snore");

    paralyze_ob = clone_object("/std/paralyze");
    paralyze_ob->set_fail_message("You are sound asleep.\n");
    paralyze_ob->set_remove_time(30);
    paralyze_ob->set_stop_message("You blink your eyes open, stretching away the "+
	"last remains of your deep sleep.\n");
    paralyze_ob->set_stop_fun("stop_paralyze");
    paralyze_ob->set_stop_object(this_object());
    paralyze_ob->move(environment(this_object()),1);

    tell_room(environment(environment(this_object())),
	QCTNAME(environment(this_object()))+"'s body suddenly appears to evaporate and fade into "+
	"the mist.\n", environment(this_object()));

    environment(this_object())->move_living("M",CORAMAR+"sleeproom", 1, 1);    
}

void
stop_paralyze()
{
    reset_euid();
    environment(this_object())->move_living("M",CORAMAR+"f1", 1, 1);
    environment(this_object())->catch_msg("You blink your eyes open, stretching away "+
	"the remains of a deep sleep. You are surprised to notice that you are not "+
	"in the same place you fell asleep.\n\n");
    tell_room(environment(environment(this_object())),
	QCTNAME(environment(this_object()))+" suddenly materializes out of the mist, "+
	environment(this_object())->query_possessive()+" shadowy form just now waking "+
	"from a deep sleep.\n", environment(this_object()));
    set_alarm(1.3, 0.0, remove_object);
}

   
    