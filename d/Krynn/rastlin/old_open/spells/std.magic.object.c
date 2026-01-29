/*
 * std.magic.object.c
 * 
 * This is an invisble object which makes sure that a continous effect
 * lasts for a period of time.
 *
 */

inherit "/d/Krynn/rastlin/open/spells/lib.effect";

#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include <macros.h>

#define DURATION_UNTIL_REBOOT -2

object spell;
object target;

static int magic_alarm_id;

int
query_magic_alarm() { return magic_alarm_id; }

void notify_dispel() {}

/*
 * Function:	qme
 * Description: Returns effected object.
 */
object
qme()
{
    return target;
}

/*
 * Function:	dispel_magic_effect
 * Arguments:	attacker - (object) : Which object caused the dispel.
 *				      Default previous object.
 *
 * Description: What to do when the spell effect is dispelled.
 */
nomask varargs void
dispel_magic_effect(object attacker = previous_object())
{
    this_object()->notify_dispel(attacker);

    if (this_object()->query_remove_on_dispel())
	qme()->remove_object();

    this_object()->remove_object();
}

/*
 * Function name: query_auto_load
 * Description:   Used to reload the effect into the player if it hasn't
 * 		  expired when he quits.  
 */
string
query_auto_load()
{
    int time_left = ftoi(get_alarm(query_magic_alarm())[2]);

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
 * Function: move_spell
 * Description:
 *	Used to initialize the spell effect object.
 * Returns:
 *	0 : If it managed to initialize the spell effect properly.
 *	string : The error message if not.
 */
nomask void
move_spell(object who, int power)
{
    object caster;
    string err_msg;
    mixed  *vars;

    spell = previous_object();
    vars = spell->query_all_variables();    

    caster = vars[0];
    target = who;

    set_power(power);

    set_element(vars[1]);
    set_duration(vars[2]);
    set_protect(vars[3]);
    set_remove_on_dispel(vars[4]);
    set_reducible(vars[5]);

    if (this_object()->move(target)!=0)
	return;

    if (query_duration() >=0)
        magic_alarm_id = set_alarm(itof(query_duration()), 0.0, "dispel_magic_effect");
}

string
stat_magic_object()
{
    string str, rest;

    str = "\nMagical effect : " + file_name(this_object()) + "\n"
	+ "Affecting      : " + file_name(qme()) + "\n"
	+ "-----------------------------------------------------\n"
	+ "Power          : " + query_power() + "\n"
	+ "Element        : " + query_element() + "\n"
	+ "Secondary elem : " + query_secondary_element() + "\n"
	+ "Previous spell : " + sprintf("%O\n", spell)
	+ "\n"
	+ "Reducible      : " + query_reducible() + "\n"
	+ "Duration       : " + query_duration() + "\n"
	+ "Time left      : " + query_time_left() + "\n"
	+ "Remove on disp : " + query_remove_on_dispel() + "\n"
	+ "\n";

    return str;
}
