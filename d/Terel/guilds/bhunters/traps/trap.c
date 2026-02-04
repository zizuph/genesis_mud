/*
 * ANONYMOUS CODE? BAAD! WHO CODED IT?
 */

#include "/d/Terel/include/Terel.h"
#include "../bhunters.h"
#include <tasks.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
inherit "/std/container";

object *elements = ({});
string name, owner_name;
float disarm_time, arm_time;
int arm_mod, trigger_mod, disarm_mod, spoiled = 0, success, tmp_trigger = 0, has_alarm = 0;
private int dAlarm, sAlarm;
object trap_shadow;
object *spoted = ({});

/* Configurates the trap */
public void configure_trap(int amod, int tmod, int dmod, float dtime, float atime, string str)
{
	arm_mod = amod;
	trigger_mod = tmod;
	disarm_mod = dmod;
	disarm_time = dtime;
	arm_time = atime;
	set_name(str);
	name = str;
}

/* Description of a trap when it's set. */
public string query_set_desc()
{
}

/* gives descriptions of disarming, ({"you disarm", "_disarms.."})*/
public string *query_disarm_desc()
{
}

public string query_owner()
{
	return owner_name;
}

/* Gives descriptions based on state if ob have spoted the trap. */
public string query_add_short(int ob)
{
	string adj = (spoiled ? "spoiled" : "set");
	if(member_array(ob, spoted) == -1)
		return "";
	return " You notice a " + adj + " " + name + " trap here.\n";
}

/* Things to do in create_object */
public void create_trap()
{
}

/* True if trap is spoiled (set wrong) */
public int query_spoiled()
{
	return spoiled;
}

/* If ob is an object it returns true if it has spoted the trap, 
 otherwise it return an array of all object that have. */
public mixed query_spoted(object ob = 0)
{
	if(!ob)
		return spoted;
	else
		return (member_array(ob, spoted) != -1);
}

/* If "" is set, it returns an element with such component_id, 
 it returns array of all elements otherwise. */
public mixed query_element(string str = "")
{
	if(!strlen(str))
		return elements;
	for(int i = 0; i < sizeof(elements); ++i)
	{
		if(elements[i]->query_component_id() == str)
			return elements[i];
	}
	return 0;
}

/* Required components 
  WARNING:
   size of this array determinates number of 'steps' in arming the trap,
it's always should be one bigger then set_phases array, if trap
doesn't need so much components, just put "" in this array so the
sizes match.
*/
string *query_component_list()
{
	return ({});
}

/* Descriptions given when trap is beeing set ({ ({"You do 1", "_does 1"}), ({"You do 2..*/
public mixed query_set_phases()
{
	return ({});
}

/* traps given living */
public void trap_me(object ob)
{
}


/* Returns 1 if ob can place this trap in his current environment */
int can_be_placed(object ob)
{
	return 1;
}

/* Checks if player spoted the trap */
public void spots(object ob)
{
	if(ob->resolve_task(trigger_mod, 
		({SKILL_WEIGHT, 50, SKILL_AVG, TS_WIS, TS_DEX, SKILL_END,
			SS_FR_TRAP, SKILL_WEIGHT, 50, SS_AWARENESS})) > 0 &&
		member_array(ob, spoted) == -1)
	{
		spoted += ({ob});
	}
}
/* ---- */

/* Modifier to disarming difuculty, based on seting success */
public int suc_mod(int i)
{
	return i/10;
}
/* ---- */

/* Notifies owner of the trap it has been triggered */
void alarm_owner()
{
	if(!objectp(find_player(owner_name)))
		return;
	find_player(owner_name)->catch_msg("Your " + query_name() + " trap has been triggered!\n");
}
/* ---- */


/* Handles trap beeing triggered */
public void trigger(object ob)
{
	if(tmp_trigger)
		return;
	if(spoiled)
		return;
	/* None is stupid enough to triger his/her own trap. */
	if(query_spoted(ob))
		return;
	tmp_trigger = 1;
	if(ob->resolve_task(trigger_mod + suc_mod(success), 
		({SKILL_WEIGHT, 50, SKILL_AVG, TS_WIS, TS_DEX, SKILL_END,
			SS_FR_TRAP, SKILL_WEIGHT, 20, SS_AWARENESS})) < 0)
	{
		ob->reveal_me(1);
		trap_me(ob);
		trap_shadow->remove_shadow();
		if(has_alarm)
			alarm_owner();
		remove_object();
	}
	tmp_trigger = 0;
}
/* ---- */


/* Handles disarming final effect, (trap is in ob inventory) */
public void disarmed_by(object ob)
{
	update_actions();
	trap_shadow->remove_shadow();
	if(ob->resolve_task(disarm_mod, 
		({SKILL_WEIGHT, 50, SKILL_AVG, TS_WIS, TS_DEX, SKILL_END,
			SS_FR_TRAP, SKILL_WEIGHT, 50, SS_SET_TRAP})) < 0)
	{
		if(spoiled)
		{
			ob->catch_msg("You failed to disarm the trap.\n");
			tell_room(E(ob), QCTNAME(ob) + " failed to disarm the trap.\n", ob);
			move(E(ob));
		}
		else
		{
			ob->catch_msg("You made a clumsy move, and you triggered the trap!\n");
			tell_room(E(ob), QCTNAME(ob) + " made a clumsy move and triggered the trap!\n", ob);
			trap_me(ob);
			remove_object();
		}
		return;
	}
	remove_prop(CONT_I_CLOSED);
	for(int i = 0; i < sizeof(elements); ++i)
	{
		if(elements[i]->move(ob))
			elements[i]->move(E(ob));
	}
	elements = ({});
	ob->catch_msg(query_disarm_desc()[0]);
	tell_room(E(ob), QCTNAME(ob) + query_disarm_desc()[1], ob);
	remove_object();
}
/* ---- */


/* Handles disarming attempt (includes move to ob inventory */
public void disarm_attempt(object ob)
{
	ob->catch_msg("You start disarming the " + name + " trap.\n");
	move(ob);
	tell_room(E(ob), QCTNAME(ob) + " starts disarming the trap.\n", ob);
	add_action("stop", "", 1);
	dAlarm = set_alarm(disarm_time, 0.0, &disarmed_by(ob));
}
/* ---- */


/* Handles arming final effect, includes moving to environment */
public void armed_by(object ob)
{
	update_actions();
	success = ob->resolve_task(arm_mod, 
		({SKILL_WEIGHT, 70, SKILL_AVG, TS_WIS, TS_INT, TS_DEX, SKILL_END,
				SS_SET_TRAP}));
	
	if(success <= 0)
		spoiled = 1;
	else
		spoiled = 0;
	/* Shadowing the environemnt */
	trap_shadow->set_me(TO);

	ob->remove_prop(LIVE_S_EXTRA_SHORT);

	string pmsg = "You fail to set the " + name + " trap. Those kind of traps seems to be to complicated for you.\n";
	string omsg = QCTNAME(ob) + " fails to set the " + name + " trap.\n";
	if(success > -300)
		pmsg = "You fail to set the " + name + " trap.\n";
	if(success > 0)
	{
		omsg = QCTNAME(ob) + " sets a trap.\n";
		pmsg = "You set the " + name + " trap.\n";
	}
	if(success > 200)
		pmsg = "You skillfully set the " + name + " trap.\n";
	if(success > 500)
		pmsg = "You amaze yourself with your skills, seting the " + name + " perfectly.\n";
	ob->catch_msg(pmsg);
	tell_room(E(ob), omsg, ob);
	
	move(E(ob));
}
/* ---- */


/* Called repeatedly to add components to the trap (trap is in ob inv) */
void arm_phase(int i, object ob)
{
	if(strlen(query_component_list()[i]))
	{
		mixed comp = ob->remove_component(query_component_list()[i]);
		if(comp == 0)
		{
			ob->catch_msg("You miss a component to finish that trap!\n");
			trap_shadow->set_me(TO);
			spoiled = 1;
			return;
		}
		/* components that can be used multiple times return 1 */
		if(objectp(comp))
		{
			elements += ({comp});
			remove_prop(CONT_I_CLOSED);
			comp->move(TO);
			add_prop(CONT_I_CLOSED, 1);
		}
	}
	/* There is just one component left */
	if(i + 1 >= sizeof(query_component_list()))
	{
		sAlarm = set_alarm(arm_time, 0.0, &armed_by(ob));
		return;
	}	
	ob->catch_msg(query_set_phases()[i][0]);
	tell_room(E(ob), QCTNAME(ob) + query_set_phases()[i][1], ob);
	sAlarm = set_alarm(arm_time, 0.0, &arm_phase(i+1, ob));
}
/* ---- */


/*  Handles arm attempt (we know ob has required components), includes moving to ob inv*/
public void arm_attempt(object ob)
{
	FIX_EUID;
	if(!can_be_placed(E(ob)))
	{
		ob->catch_msg("That trap can't be set here.\n");
		remove_object();
		return;
	}
	if(stringp(E(TO)->have_trap()))
	{
		ob->catch_msg("There is one trap set here already.\n");
		remove_object();
		return;
	}
	
	move(ob);
	
	ob->catch_msg("You start seting the " + name + " trap.\n");
	tell_room(E(ob), QCTNAME(ob) + " starts seting a trap.\n", ob);
	
	owner_name = ob->query_real_name();
	ob->add_prop(LIVE_S_EXTRA_SHORT, " seting a trap");
	trap_shadow = clone_object(TRAP_SHADOW);
	trap_shadow->shadow_me(E(ob));
	
	add_action("stop", "", 1);
	arm_phase(0, ob);
	
	/* Player sees his own traps */
	spoted += ({ob});
}
/* ---- */	
	

/* from /std/heap.c */
varargs int stop(string str)
{
    if (query_verb() == "stop")
    {
        update_actions();
	if(pointerp(get_alarm((dAlarm))))
	{
		remove_alarm(dAlarm);
		write("You stop disarming the trap.\n");
		say(QCTNAME(this_player()) + " stops disarming the trap.\n");
		return 1;
	}
	if(pointerp(get_alarm((sAlarm))))
	{
		remove_alarm(sAlarm);
		write("You stop seting the trap, now it's spoiled.\n");
		TP->remove_prop(LIVE_S_EXTRA_SHORT);
		say(QCTNAME(this_player()) + " stops seting the trap.\n");
		trap_shadow->set_me(TO);
		spoiled = 1;
		return 1;
	}
    }

    /* Allow wizards and allow commands that are allowed. */
    if (this_player()->query_wiz_level() ||
        CMDPARSE_PARALYZE_CMD_IS_ALLOWED(query_verb()))
    {
        /* When quitting, update the actions, so people can drop stuff. */
        if (query_verb() == "quit")
        {
            update_actions();
        }
        return 0;
    }

    write("You completely focused on " + (pointerp(get_alarm((sAlarm))) ? "seting" : "disarming") +
	" the trap at the moment, you can 'stop' if you want to do something else.\n");
    return 1;
}

/* At no point trap shadow can exist without its trap */
public void remove_object()
{	
	elements->remove_object();
	if(objectp(trap_shadow))
		trap_shadow->remove_shadow();
	::remove_object();
}

public void init()
{
	::init();
	/* If this action would be added in cmd_item, player that can't
	see the trap would still get 'Disarm what?' when trying to disarm. */
	add_action("disarm_trap", "disarm");
}

void create_container()
{
	set_name("blah");
	add_prop(CONT_I_WEIGHT, 0);
	add_prop(CONT_I_VOLUME, 0);
	add_prop(CONT_I_MAX_VOLUME, 1000000);
	add_prop(CONT_I_MAX_WEIGHT, 1000000);
	add_prop(OBJ_I_VALUE, 0);
	add_prop(CONT_I_CLOSED, 1);
	set_no_show();
	create_trap();
}

/* Actions */

int disarm_trap(string a)
{
	if(member_array(TP, spoted) == -1)
	{
		notify_fail("What?\n");
		return 0;
	}
	if(a != "trap" && a != name && a != name + " trap")
	{
		notify_fail("Disarm what?\n");
		return 0;
	}
	disarm_attempt(TP);
	return 1;
}

/* Attaching alarm to the trap */

public int attach_alarm(object alarm)
{
	if(has_alarm)
		return 0;
	alarm->remove_object;
	has_alarm = 1;
	return 1;
}
