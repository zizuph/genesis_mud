/*
    feeding.c

    Inheritable module for feeding livings.

    Copyright by Wout de Zeeuw, Fysix@Genesis, May 1997

    Modified by Trofast, November 1999 to fix a feeding bug.
    Check do_feed() for details.

 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include "default.h"

// Global variables
string* Allowed_food = ({ });

/* Function name: light_fail
 * Description:   We fail to do something because it is dark?
 * Arguments:     string - the object string
 * Returns:       int 0 if failed
 */
varargs int
light_fail(string str)
{
    string s;

    if (!strlen(str))
	    str = query_verb() + " things";
#ifdef GENESIS
    if (!stringp(s = environment(this_player())->query_prop(ROOM_S_DARK_MSG)))
#endif
	notify_fail("It is too dark to " + str + ".\n");
#ifdef GENESIS
    else
	notify_fail(s + " " + str + ".\n");
#endif
    return 0;
}

/* Function name: can_feed
 * Description:   Is this object something that is accepted by food by this
 *                living?
 * Arguments:     object, the food object
 * Returns:       int 0 - false, 1 - true
 */
public int
can_feed(object food)
{
    int i = sizeof(Allowed_food);

    while (i--)
        if (food->id(Allowed_food[i]))
            return 1;

    notify_fail(capitalize(food->short()) + 
        " is not accepted as food.\n");
    return 0;
}

/* Function name: query_allowed_food
 * Description:   What kinds of food are allowed for this living for feeding?
 * Returns:       string* - an array of food names
 */
public string*
query_allowed_food()
{
    return Allowed_food;
}

/* Function name: set_allowed_food
 * Description:   Set the kinds of food that this living is allowed to
 *                be fed with.
 * Arguments:     mixed - a string or array of strings describing the food
 */
public void
set_allowed_food(mixed t)
{
    if (stringp(t))
        t = ({ t });
    if (pointerp(t))
        Allowed_food = t;
}

/* Function name: hook_fail_eat
 * Description:   Drop the food on the floor and give a message
 *                that we fail to eat.
 * Arguments:     object food
 */
public void
hook_fail_eat(object food)
{
    tell_room(environment(this_object()),
        capitalize(food->short()) + " is too much for " +
        QTNAME(this_object()) + " and " + this_object()->query_pronoun() +
        " drops it on the floor.\n",
        this_object());
    food->move(environment(this_object()), 1);
}

/* Function name: hook_feed
 * Description:   Tell everybody that the feeder is feeding me.
 * Arguments:     object feeder, object food
 */
public void
hook_feed(object feeder, object food)
{
    feeder->catch_tell("You feed the " + this_object()->short(feeder) +
        " with " + food->short() + ".\n");
    tell_room(environment(this_object()),
        QCTNAME(feeder) + " feeds the " +
        QTNAME(this_object()) + " with " + food->short() + ".\n",
        ({feeder, this_object()}));
}

/* Function name: hook_fail_food_move
 * Description:   Move the food to the floor and give a message
 *                that the food failed to move inside me.
 * Arguments:     object feeder, object food
 */
public void
hook_fail_food_move(object feeder, object food)
{
    food->move(environment(feeder), 1);

    feeder->catch_tell("You try to feed the " +
        this_object()->short(feeder) +
        " with " + food->short() +
        " but it is too heavy and drops on the floor.\n");
    tell_room(environment(this_object()),
        QCTNAME(feeder) + " tries to feed the " +
        QTNAME(this_object()) + " with " + food->short() +
        " but it is too heavy and drops on the floor.\n",
        ({feeder, this_object()}));
}

/* Function name: do_feed
 * Description:   Try to feed this living.
 * Arguments:     object - the food object
 *                object - feeder, defaults to this_player()
 * Returns:       int 0 - failed feeding, 1 - success
 */
public varargs int
do_feed(object o, object feeder)
{
  object TO=this_object();


    // Check if we can eat this
    if (!can_feed(o))
        return 0;

    if (!objectp(feeder))
        feeder = this_player();

    // Transfer food and eat
    if (o->move(TO) == 0)
    {
       hook_feed(feeder, o);

       // This doesn't work. Command("eat all") still returns a
       // value if the living is too full to eat.
       // Try to eat, otherwise drop on the floor
       //       if (!command("eat all"))
       //       {
       //            hook_fail_eat(o);
       //        }

       // Instead, use this to make sure the steed can eat it.

       if (!TO->eat_food(o->query_amount(),1))
	 {
	   hook_fail_eat(o);
	 }

       command("eat all");
    }
    else // the move failed, drop food on the floor
    {
        hook_fail_food_move(feeder, o);
    }

    return 1;
}

/* Function name: feed
 * Description:   Action for feeding animals. Makes a call to do_feed(mixed)
 *                in the object, as defined in feeding.c. do_feed should
 *                handle the actual feeding.
 * Arguments:     string - the arguments after the feed command
 * Returns:       int 1 - succesful, 0 - failed
 */
public nomask int
feed(string s)
{
    object *living_list, living, *food_list, food;
    string s1, s2;

    if (CAN_SEE_IN_ROOM(this_player()) <= 0)
        return light_fail("see");

    notify_fail("Feed whom with what?\n");
    if (!stringp(s))
        return 0;

    if (!parse_command(s, all_inventory(environment(this_player())),
        "%s 'with' %s", s1, s2))
        return 0;

    living_list = FIND_STR_IN_ARR(s1, all_inventory(environment(this_player())));
    if (sizeof(living_list) != 1)
        return 0;

    living = living_list[0];

    food_list = FIND_STR_IN_ARR(s2, all_inventory(this_player()));
    if (sizeof(food_list) == 0)
        return 0;

    notify_fail("Try to feed the " + living->short() + " with one thing " +
        "at a time.\n");
    if (sizeof(food_list) > 1)
        return 0;

    food = food_list[0];
    return living->do_feed(food, this_player());
}

