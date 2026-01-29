/*  Obscure.h
 * Code to let a player (specifically the Rangers) obscure their trail
 * to make it harder for them to be tracked.
 * One can obscure trail, which is fast but very chancy, or 
 * obscure trail carefully, which is slower but more reliable.
 * Success and speed depend on SS_TRACKING and SS_WIS of the player.
 * 
 * Mayhem Liege of Emerald
 * 8 Dec, 1994
 * 
 * Revision history:
 * 
 * Gwyneth 2/9/04- Changed error for no argument from What? to Obscure what?
 */

#ifndef OBSCURE
#define OBSCURE 1
#include "/d/Gondor/defs.h"
#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <macros.h>

#define TIME 2
#define NORM_TIME 3
#define FAT_COST 5 
int alarm_id;

int obscure(string str, object room) 
{
    object paralyze;
    room = TP->query_prop(LIVE_O_LAST_ROOM);
    if(!str) { notify_fail("Obscure what?\n"); return 0; }

    if(!room->query_prop(ROOM_I_IS))
    {
	notify_fail("There is no trail to obscure here!\n");
	return 0;
    }

    if(!CAN_SEE_IN_ROOM(TP))
    { 
	notify_fail("You can't see your hand in front of your face, "+
	  "let alone the trail behind you.\n");
	return 0;
    }

    if(TP->query_fatigue() < FAT_COST)
    { 
	notify_fail("You are too tired to do that.\n");
	return 0;
    }

    FIX_EUID;
    paralyze = clone_object("/std/paralyze");
    paralyze->set_standard_paralyze("tracking");
    paralyze->set_stop_fun("do_stop");
    paralyze->set_stop_verb("stop");
    paralyze->set_stop_message("You stop obscuring the trail behind "+
      "you.\n");
    paralyze->set_fail_message("You are busy obscuring the trail behind "+
      "you.  You must 'stop' or finish to do something else.\n");

    switch(str)
    {
    case "trail":
	write("You begin obscuring the path behind you.\n");
	say(QCTNAME(this_player())+" bends down and starts doing "+
	  "something to the trail behind "+OBJECTIVE(TP)+".\n");
	paralyze->set_remove_time(NORM_TIME);
	paralyze->move(TP,1);
	TP->add_fatigue(-FAT_COST);
	if(TP->resolve_task(TASK_DIFFICULT,({TS_WIS,SS_TRACKING})) > 0)
	    alarm_id = set_alarm(NORM_TIME.0,0.0,"do_obscure",TP,room);
	else
	    alarm_id = set_alarm(NORM_TIME.0,0.0,"do_done",TP);
	break;
    case "trail carefully":
	write("You begin obscuring the path behind you.\n");
	say(QCTNAME(this_player())+" bends down and starts doing "+
	  "something to the trail behind "+OBJECTIVE(TP)+".\n");
	paralyze->set_remove_time(TIME);
	paralyze->move(TP,1);
	if(TP->resolve_task(TASK_ROUTINE,({TS_WIS,SS_TRACKING})) > 0)
	    alarm_id = set_alarm(itof(TIME),0.0,"do_obscure",TP,room);
	else
	    alarm_id = set_alarm(itof(TIME),0.0,"do_done",TP);
	break;
    default:
	notify_fail("Obscure what?\n");
	return 0;
	break;
    }
    return 1;
}


varargs int do_stop(mixed arg)
{
    if(!objectp(arg))
	remove_alarm(alarm_id);
    say(QCTNAME(TP) + " straightens back up, having finished "+
      POSSESSIVE(TP) + " work.\n");
    /*
      tell_room(ENV(TP),QCTNAME(TP)+" stops obscuring the trail behind "+ 
	OBJECTIVE(TP)+".\n",TP);
    */
    return 0;
}


public int do_done(object who)
{
    write("You believe you have obscured the trail behind you.\n");
    return 1;
}


public int do_obscure(object who, object room)
{
    room->remove_prop(ROOM_S_DIR);
    do_done(who);
    return 1;
}
#endif
