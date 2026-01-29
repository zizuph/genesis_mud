/*
 * std.magic.shadow.c
 * 
 * This is an invisble object which makes sure that a continous effect
 * lasts for a period of time.
 *
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include <macros.h>

inherit "/std/shadow";

static int gMagic_alarm;

int gPower,
    gDuration,
    gRemove_obj,
    gElement,
    gForm;

object gEnv;

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
query_me() { return gEnv; }

/*
 * Function:	dispel_magic
 * Arguments:	attacker - (object) : Which object caused the dispel.
 *				      Default previous object.
 *
 * Description: What to do when the spell effect is dispelled.
 */
nomask varargs void
dispel_magic(object attacker = previous_object())
{
    this_object()->notify_dispel_magic(attacker);

    gEnv->remove_magic_effect(this_object());

    if (gRemove_obj)
	remove_object();
    else
        remove_shadow();
}

/*
 * Function:    move_spell
 * Description: Move the spell object to the environment and
 *              activate it.
 * Arguments:   env - The environment to move it too.
 * Returns:     True if everything went ok, false otherwise.
 */
nomask int
move_spell(object caster, object target, object prev)
{
    if (!objectp(target))
        return 0;

    gEnv = target;

    if (!shadow_me(gEnv))
    {
        this_object()->remove_object();
	return 0;
    }

    if (gDuration >=0)
        gMagic_alarm = set_alarm(itof(gDuration), 0.0, "dispel_magic");

    gEnv->add_magic_effect(this_object());

    this_object()->init_spell(caster, gEnv, prev);

    return 1;
}

string
stat_object()
{
    string str, rest;

    str = gEnv->stat_object();

    str += "\nMagical effect : " + file_name(this_object()) + "\n"
	+ "Shadowing      : " + file_name(gEnv) + "\n"
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

