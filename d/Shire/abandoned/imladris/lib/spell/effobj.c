/*
 * effobj.c
 * 
 * This is an invisble object which makes sure that a continous effect
 * lasts for a period of time.
 *
 */

inherit "/std/object";

#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include <macros.h>

#include "spell.h"
#include "effect.h"

object spell;
object target;
int alarm_id,alarmid2,alarmid3;

void notify_dispel() {}

void
create_object()
{
    set_no_show();
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);
}

void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    target = environment(this_object());
    if (!living(target))
	 return;
 
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);
}

/*
 * Function:	qme
 * Description: Returns effected object.
 */
object
qme()
{
    return target;
}

int
is_effect()
{
    return EFFECT_OBJECT;
}

/*
 * Function:	dispel_effect
 * Arguments:	attacker - (object) : Which object caused the dispell.
 *				      Default previous object.
 *
 * Description: What to do when the spell effect is dispelled.
 */
nomask varargs void
dispel_effect(object attacker = previous_object())
{
    this_object()->notify_dispel(attacker);

    if (this_object()->query_remove_on_dispel())
	qme()->remove_object();

    remove_object();
}

#include "reducing.c"

/*
 * Function name: query_auto_load
 * Description:   Used to reload the effect into the player if it hasn't
 * 		  expired when he quits.  
 */
string
query_auto_load()
{
	int time_left = get_alarm(alarm_id);
    //int time_left = find_call_out("dispel_effect");

    if (query_duration() == DURATION_UNTIL_REBOOT)
	return MASTER + ":" + DURATION_UNTIL_REBOOT;
    else
	return MASTER + ":" + time_left;
}

/*
 * Function name: init_arg
 * Description:   Parses the data from the saved object.
 */
void
init_arg(string arg)
{
    string *arglist;
    int time;

    arglist = explode(arg,",");

    sscanf(arglist[0], "%d", time);
    set_duration(time);
}

/*
 * Function: init_object
 * Description:
 *	Used to initialize the spell effect object.
 * Returns:
 *	0 : If it managed to initialize the spell effect properly.
 *	string : The error message if not.
 */
nomask varargs mixed
init_object(object who, int power)
{
    object caster;
    string err_msg;
	int the_time;

    spell  = previous_object();
    caster = spell->query_caster();
    target = who;

    set_reducible(0);
    set_power(power);
    set_duration(10*60);

    if (function_exists("create_object", spell) == STD_SPELL_FILE)
	set_element(spell->query_prop(SPELL_I_ELEMENT_SKILL));

    effect_remove = 0;

    err_msg = this_object()->init_effect(spell, caster, power);

	the_time = query_duration();
    if(!stringp(err_msg))
    {
	if (move(target)!=0)
	    return "Target can't be effected.\n";
	if (the_time >= 0)
		alarm_id = set_alarm(the_time,0.0, &dispel_effect);
/*	if (query_duration() >=0)
	    call_out("dispel_effect", query_duration());
*/
	return 0;
    }
    else
    {
	alarm_id2 = set_alarm(0.0,0.0, &remove_object);
	//call_out("remove_object", 0);
	return err_msg;
    }
}


string
stat_object()
{
    string str, rest;

    str = "\nMagical effect : " + file_name(this_object()) + "\n"
	+ "Affecting      : " + file_name(qme()) + "\n"
	+ "-----------------------------------------------------\n"
	+ "Power          : " + query_power() + "\n"
	+ "Attack         : " + query_attack_proc() + "%\n"
	+ "Defense        : " + query_defense_proc() + "%\n"
	+ "Element        : " + query_element() + "\n"
	+ "Secondary elem : " + query_secondary_element() + "\n"
	+ "Previous spell : " + sprintf("%O\n", spell)
	+ "\n"
	+ "Reducible      : " + query_reducible() + "\n"
	+ "Duration       : " + query_duration() + "\n"
	+ "Time left      : " + query_time_left() + "\n"
	+ "Remove on disp : " + query_remove_on_dispel() + "\n"
	+ "\n";

    rest = ::stat_object();
    if (strlen(rest))
	return str + rest;
    else
	return str;
}
