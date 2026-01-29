/*
 * Sequence Example: 0, "raise 'hands'", "raise_hands", 
 *                   1, "kneel [before] [the] 'flame'", "kneel_flame"
 */
inherit "/std/object";

#include <macros.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <stdproperties.h>

#include "../defs.h"

#define CEREMONY_MASTER     0
#define CEREMONY_TARGET     1

//#define DEBUG(x)  find_player("lucius")->catch_tell("CER:"+ x +"\n")
#define DEBUG(x)

private int ind, size;
private object master, target;
private mixed *sequence = ({ });


public void
create_ceremony(void)
{
}

public nomask void
create_object(void)
{
    reset_euid();
    set_name("ceremony");
    set_short("ceremony");

    add_name("_union_ceremony_object");

    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    add_prop(OBJ_M_NO_GET, 1);

    set_no_show();
    create_ceremony();

    /* Get rid of 'stale' ceremonies */
    if (IS_CLONE)
	set_alarm(2000.0, 0.0, remove_object);
}

public void
set_ceremony_sequence(mixed *seq)
{
    DEBUG("set_ceremony_sequence()");
    if (!pointerp(seq))
	return;

    ind  = 0;
    sequence = seq;
    size = sizeof(sequence);
}

/*
 * valid_master() - this should be masked in the specific ceremony
 *   to see if who is a valid ceremony master.
 *   This function should also set the notify_fail() for failures.
 */
public varargs int
valid_master(object who, object for_obj)
{
    if (!objectp(who))
	who = this_player();

    if (!objectp(for_obj))
	for_obj = who;

    return 1;
}

/*
 * valid_target() - this should be masked in the specific ceremony
 *   to see if who is a valid ceremony target.
 *   This function should also set the notify_fail() for failures.
 */
public varargs int
valid_target(object who = this_player(), object for_obj = who)
{
    return 1;
}

/*
 * valid_ceremony() - this functions should be masked to check to
 *   see if the ceremony can be performed at all. A typical check
 *   would be to see if the ceremony object is in a certain room or domain.
 */
public int
valid_ceremony(void)
{
    return 1;
}

public int
set_ceremony_master(object who)
{
    if (!valid_master(who))
	return 0;

    master = who;
    return 1;
}

public object
query_ceremony_master(void)
{
    return master;
}

public int
set_ceremony_target(object who)
{
    if (!valid_target(who))
	return 0;

    target = who;
    return 1;
}

public object
query_ceremony_target(void)
{
    return target;
}

/*
 * The core of the ceremony actions. It checks the argument against the parsing list,
 * checks for a string variable (if it finds one, it sends it as
 * an argument to the function), and checks to see if the
 * actor is a valid master or target, depending on whether
 * the ceremony action is for the master or target.
 *
 * E.g., The ceremony part:
 *   ({ 0, "kneel/bow %s [before] [the] 'flame' / 'Fire', "bow_flame" })
 *
 * Will do the following: 
 *   1. Did the parsing of the argument succeed?
 *   2. Is the person performing the action the ceremony target?
 *   3. if so, call the function bow_flame(str) with the string variable.
 *
 * Therefore, and checking for the variable is done in the function
 * itself.
 */
public int
ceremony_action(string str)
{
    string act, *rem, arg;

    DEBUG("ceremony_action()");
    if (ind > size)
	return 0;

    notify_fail(CAP(query_verb()) + " what?\n");
    if (!strlen(str))
        return 0;

    DEBUG(sequence[ind]);
    rem = explode(sequence[ind + 1], " ")[1..];
    act = implode(rem, " ");
    DEBUG(act);

    if (wildmatch("*%s*", act))
    {
        if (!parse_command(str, ({}), act, arg))
            return 0;
    }
    else if (!parse_command(str, ({}), act))
        return 0;

    if (!sequence[ind] && !valid_master(TP))
        return 0;
    else if (sequence[ind] && !valid_target(TP))
        return 0;

    if (!call_other(TO, sequence[ind + 2], arg))
        return 0;

    ind += 3;

    /* We reached the end of the ceremony, remove the object after a short delay */
    if (ind > size)
       set_alarm(20.0, 0.0, remove_object);

    return 1;
}

public object
get_present(string str)
{
    object *things = FIND_STR_IN_OBJECT(str, ENV(TO));

    if (sizeof(things))
        return things[0];
    else
        return 0;
}

public string
ceremony_help(void)
{
    return 0;
}

public int
help(string str)
{
    if (str != "ceremony" || TP != master)
        return 0;

    if (!strlen(ceremony_help()))
    {
        write("There is no help available for this ceremony.\n");
        return 1;
    }

    write(ceremony_help());
    return 1;
}

/*
 * Add all the valid actions to the players. That is, the ceremony master
 * will get the master commands, the target will get the target commands.
 * So the ceremony part:
 * 	({ 0, "kneel/bow %s [before] [the] 'flame' / 'Fire', "bow_flame" })
 * will add the actions "kneel" and "bow" to the ceremony target.
 */
public void
init(void)
{
    object *whom, player = TP;

    ::init();

    if (!ENV(TO))
        return;

    if (!query_interactive(player))
	return;

    add_action(help, "help");

    DEBUG("Master:    " + master->query_name());
    DEBUG("Target:    " + target->query_name());

    whom = filter(all_inventory(environment()), query_interactive);
    foreach(object who: whom)
    {
	int size = sizeof(sequence);
	set_this_player(who);
	DEBUG("WHO: " + who->query_name());
	for(int i = 0; i < size; i += 3)
	{
	   string verb = explode(sequence[i+1], " ")[0];
	   DEBUG("Checking verb " + verb);
	   if (((sequence[i] == CEREMONY_MASTER) && (TP == master)) ||
	       ((sequence[i] == CEREMONY_TARGET) && (TP == target)))
	   {
	       foreach(string vb: explode(verb, "/"))
	       {
		   add_action(ceremony_action, vb);
		   DEBUG("Adding " + vb + " to " + TP->query_name());
	       }
	   }
       }
    }
    set_this_player(player);
}
