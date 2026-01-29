/*
 * magic.object.c
 * 
 * This is an invisble object which makes sure that a continous effect
 * lasts for a period of time.
 *
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include <macros.h>

// inherit "/std/object";

#define DURATION_UNTIL_REBOOT -2

static int gMagic_alarm;

int gPower,
    gDuration,
    gRemove_obj,
    gElement,
    gForm;

object gMaster;

/*
 * Function:    set_element
 * Description: Set the element of this spell object.
 * Arguments:   elem - The element, as found in /sys/ss_types.h
 */
public void
set_element(int elem) { gElement = elem; }

/*
 * Function:    set_form
 * Description: Set the form of this spell object.
 * Arguments:   from - The form, as found in /sys/ss_types.h
 */
public void
set_form(int form) { gForm = form; }

/*
 * Function:    set_power
 * Description: Set the power of this spell object.
 * Arguments:   power - The power.
 */
public void
set_power(int power) { gPower = power; }

/*
 * Function:    set_remove_on_dispel
 * Description: Set this and the affected object will be removed
 *              when the spell is dispeled.
 * Arguments:   power - The power.
 */
public void
set_remove_on_dispel() { gRemove_obj = 1; }

/*
 * Function:    set_duration
 * Description: Set the duration of this spell object.
 * Arguments:   time - The duration.
 */
public void
set_duration(int time) { gDuration = time; }

/*
 * Function:    query_element
 * Returns:     The element of this spell object
 */
public int
query_element() { return gElement; }

/*
 * Function:    query_form
 * Returns:     The form of this spell object
 */
public int
query_form() { return gForm; }

/*
 * Function:    query_power
 * Returns:     The power of this spell object
 */
public int
query_power() { return gPower; }

/*
 * Function:    query_duration
 * Returns:     The duration of this spell object
 */
public int
query_duration() { return gDuration; }

/*
 * Function:    query_remove_on_dispel
 * Returns:     True or false if the object should be removed or not.
 */
public int
query_remove_on_dispel() { return gRemove_obj; }

/*
 * Function:	query_me
 * Description: Returns effected object.
 */
public object
query_me() { return gMaster; }

/*
 * Function:    notify_spell_dispel
 * Description: This function get called when a spell is dispeled
 * Arguments:   ob - The object that caused the dispel
 */
public void
notify_dispel_magic(object ob)
{
}

/*
 * Function:	dispel_magic
 * Arguments:	attacker - (object) : Which object caused the dispel.
 *				      Default previous object.
 *
 * Description: What to do when the spell effect is dispelled.
 */
nomask public void
dispel_magic()
{
    notify_dispel_magic(previous_object());

    gMaster->remove_magic_effect(this_object());

    if (gRemove_obj)
	gMaster->remove_object();

    this_object()->remove_object();
}

/*
 * Function name: query_auto_load
 * Description:   Used to reload the effect into the player if it hasn't
 * 		  expired when he quits.  
 *
string
query_auto_load()
{
    int time_left = ftoi(get_alarm(gMagic_alarm)[2]);

    if (gDuration == DURATION_UNTIL_REBOOT)
	return MASTER + ":" + DURATION_UNTIL_REBOOT;
    else
	return MASTER + ":" + time_left;
}
*/

/*
 * Function name: init_arg
 * Description:   Parses the data from the saved object.
 */
void
init_arg(string arg)
{
    string *arglist;
    int time;

    find_player("rastlin")->catch_msg(arg);

    arglist = explode(arg,":");

    sscanf(arglist[0], "%d", time);
    set_duration(time);
}

/*
 * Function:    move_spell
 * Description: Move the spell object to the environment and
 *              activate it.
 * Arguments:   env - The environment to move it too.
 * Returns:     True if everything went ok, false otherwise.
 */
nomask public int
move_spell(object caster, object target, object prev)
{
    gMaster = target;

    if (this_object()->move(gMaster))
    {
	/* check added by Aridor, 11/14/95, because i want
	 * spells to work for non-container objects as well.
	 * we move to the environment in that case.
	 * This is not the perfect solution (just think about
	 * moving the object, whereas the spell_effect will stay).
	 * but the thing i need it for is an instant spell, so it
	 * doesn't matter where the object is, as long as it's there
	 * and not destructed. :)  Eventually, a better solution must
	 * be found!
	 */
	if (this_object()->move(environment(gMaster)))
	  {
	      this_object()->remove_object();
	      return 0;
	  }
    }

    if (gDuration >=0)
        gMagic_alarm = set_alarm(itof(gDuration), 0.0, "dispel_magic");

    gMaster->add_magic_effect(this_object());

    this_object()->init_spell(caster, target, prev);

    return 1;
}

string
stat_magic_object()
{
    string str, rest;

    str = "\nMagical effect : " + file_name(this_object()) + "\n"
	+ "Affecting      : " + file_name(gMaster) + "\n"
	+ "-----------------------------------------------------\n"
	+ "Power          : " + gPower + "\n"
	+ "Element        : " + gElement + "\n"
	  /*	+ "Secondary elem : " + query_secondary_element() + "\n"*/
	  /*	+ "Previous spell : " + sprintf("%O\n", spell)*/
	+ "\n"
	  /*	+ "Reducible      : " + query_reducible() + "\n"*/
	+ "Duration       : " + gDuration + "\n"
	  /*	+ "Time left      : " + query_time_left() + "\n"*/
	+ "Remove on disp : " + gRemove_obj + "\n"
	+ "\n";

    return str;
}







