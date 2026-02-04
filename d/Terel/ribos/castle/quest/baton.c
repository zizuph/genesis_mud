/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * Tom's baton
 *
 * modified by Sorgum 950707
 * modified by Lilith Feb, 2009
 * modified by Petros Apr, 2009 - removed ability to force someone to
 *                                leave the room. Added extra checks
 *  Stuff here in the treasure rooms are boring.
 *  Lets make them more interesting -- worthy
 *  of a King's treasure house.
 */

#include <cmdparse.h>
#include "/d/Terel/include/Terel.h"

inherit STDOBJECT;
inherit "/lib/commands";
inherit "/lib/keep";

#define MAX_TIMES 5
#define THRUST_PROP     "_live_i_thrust_baton"

int no_times = 0;

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    ::create_object();
    set_name("baton");
    set_short("Tom's Baton");
    set_long("This is the baton Tom uses to tell his followers what " +
	     "to do.  He also uses it, on occasion, to punish his " +
	     "unworthy followers by thrusting it into their chests.  " +
	     "Its not a weapon, as you would have to be like Tom " +
	     "to use it as such.....and you are not like Tom.\n");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE,  10);
}

int
do_thrust(string str)
{
    object target;

    if (!strlen(str)
        || !objectp(target = PARSE_COMMAND_ONE(str, 0, " [into] [the] [chest] [of] %l ")))
    {
        notify_fail("At whom do you want to thrust the baton?\n");
        return 0;
    }

    if (TP->query_attack() != target)
    {
        notify_fail("You need to be fighting someone to thrust this "
            + short() + " at them!\n");
        return 0;
    }
    
    if (no_times > MAX_TIMES)
    {
        notify_fail("It is too damaged to be useful for further thrusting.\n");
        return 0;
    }

    if (query_prop(THRUST_PROP) + 15 > time()
        || TP->query_prop(THRUST_PROP) + 15 > time())
    {
        notify_fail("It's too soon to thrust the baton again!\n");
        return 0;
    }
    
    add_prop(THRUST_PROP, time());
    TP->add_prop(THRUST_PROP, time());
    
    if (!random(2))
    {
        // 50% chance of missing the thrust
        TP->catch_msg("You thrust the " + short() + " at " + QTNAME(target)
            + ", but you miss completely.\n");
        target->catch_msg(QCTNAME(TP) + " thrusts a " + short() + " at "
            + "you, but " + TP->query_pronoun() + " misses completely.\n");
        tell_room(environment(TP), QCTNAME(TP) + " thrusts a " + short()
            + " at " + QTNAME(target) + ", but " + TP->query_pronoun()
            + " misses completely.\n", ({ TP, target }));         
        return 1;
    }

    say(QCTNAME(TP) +" thrusts something into "+ QNAME(target) + 
        "'s chest.\n"+ QCTNAME(target) +" stumbles backwards.\n", ({ this_player(), target }));
    target->catch_msg(QCTNAME(TP) +" hit you in the chest with something hard! "+
        "You stumble backwards.\n");
    TP->catch_msg(QCTNAME(target) +" stumbles backwards from the force of your thrust.\n");

    // Add an attack delay for the duration of one round
    target->add_attack_delay(5);

    /* This counter limits the number of thrusts */
    no_times++;  

    if (no_times > MAX_TIMES)
    {
        write("The baton cracks. It is now too damaged to be "+
            "useful for further thrusting.\n");
        tell_room(environment(TP), "The " + short() + " cracks in "
            + QTNAME(TP) + "'s hands. It looks broken.\n", ({ TP }));
    }
    
    return 1;

}

void
init()
{
    ::init();
    add_action(do_thrust,    "thrust");
    add_action(do_thrust,    "batonthrust");

}

