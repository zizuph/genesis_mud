/*
 * feeding.c
 *
 * Inheritable module for feeding livings.
 *
 * Copyright by Wout de Zeeuw, Fysix@Genesis, May 1997
 *
 * Revision History:
 * ----------------
 *
 * - Modified by Trofast, November 1999 to fix a feeding bug.
 * - Recoded by Lucius, April 2000
 *
 */

#pragma no_clone
#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <composite.h>
#include <stdproperties.h>

static string *allowed_food = ({});

/*
 * Function name: can_feed
 * Description:   Is this object something that is accepted by food by this
 *                living?
 * Arguments:     object, the food object
 * Returns:       int 0 - false, 1 - true
 */
public int
steed_can_feed(object food)
{
    int i = sizeof(allowed_food);

    while (i--)
	if (food->id(allowed_food[i]))
	    return 1;

    notify_fail(capitalize(food->short()) + 
      " is not accepted as food.\n");
    return 0;
}

/*
 * Function name: query_allowed_food
 * Description:   What kinds of food are allowed for this living for feeding?
 * Returns:       string* - an array of food names
 */
public string *
query_steed_allowed_food()
{
    return allowed_food;
}

/*
 * Function name: set_allowed_food
 * Description:   Set the kinds of food that this living is allowed to
 *                be fed with.
 * Arguments:     mixed - a string or array of strings describing the food
 */
public void
set_steed_allowed_food(mixed t)
{
    if (!pointerp(t))
    {
	t = ({ t });
    }

    allowed_food = t;
}

/*
 * Function name: hook_fail_eat
 * Description:   Drop the food on the floor and give a message
 *                that we fail to eat.
 * Arguments:     object food
 */
public void
st_hook_fail_eat(object food)
{
    tell_room(environment(this_object()),
      capitalize(food->short()) + " is too much for " +
      QTNAME(this_object()) + " and " + this_object()->query_pronoun() +
      " drops it on the floor.\n",
      this_object());
    food->move(environment());
}

/*
 * Function name: hook_feed
 * Description:   Tell everybody that the feeder is feeding me.
 * Arguments:     object feeder, object food
 */
public void
st_hook_feed(object feeder, object food)
{
    feeder->catch_tell("You feed the " + this_object()->short(feeder) +
      " with " + food->short() + ".\n");
    tell_room(environment(this_object()),
      QCTNAME(feeder) + " feeds the " +
      QTNAME(this_object()) + " with " + food->short() + ".\n",
      ({feeder, this_object()}));
}

/*
 * Function name: hook_fail_food_move
 * Description:   Move the food to the floor and give a message
 *                that the food failed to move inside me.
 * Arguments:     object feeder, object food
 */
public void
st_hook_fail_food_move(object feeder, object food)
{
    food->move(environment(feeder));

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

/*
 * Function name: do_feed
 * Description:   Try to feed this living.
 * Arguments:     object - the food object
 *                object - feeder, defaults to this_player()
 * Returns:       int 0 - failed feeding, 1 - success
 */
public varargs int
steed_do_feed(object food, object feeder)
{
    if (!feeder || !food)
	return 0;

    if (!steed_can_feed(food))
	return 0;

    if (food->move(this_object()) == 0)
    {
	st_hook_feed(feeder, food);

	if (!this_object()->eat_food(food->query_amount(), 1))
	{
	    st_hook_fail_eat(food);
	}

	command("eat all");
    }
    else
    {
	st_hook_fail_food_move(feeder, food);
    }

    return 1;
}

/*
 * Function name: feed
 * Description:   Action for feeding animals. Makes a call to do_feed(mixed)
 *                in the object, as defined in feeding.c. do_feed should
 *                handle the actual feeding.
 * Arguments:     string - the arguments after the feed command
 * Returns:       int 1 - succesful, 0 - failed
 */
public nomask int
feed(string str)
{
    object food;
    mixed  tmp;

    if (!str)
    {
	notify_fail("Feed what with what?\n");
	return 0;
    }

    if (!CAN_SEE_IN_ROOM(this_player()))
    {
	tmp = environment(this_player())->query_prop(ROOM_S_DARK_LONG);
	if (tmp)
	{
	    notify_fail(tmp);
	    return 0;
	}

	tmp = environment(this_player())->query_prop(ROOM_S_DARK_MSG);
	if (tmp)
	{
	    notify_fail(tmp + " feed " + str);
	    return 0;
	}

	notify_fail("It is too dark here to feed "+ str);
	return 0;
    }
	
    tmp  = all_inventory(environment(this_player()));
    tmp += all_inventory(this_player());

    if (!parse_command(str, tmp, "%l 'with' %o", tmp, food))
    {
	notify_fail("Feed what with what?\n");
	return 0;
    }

    if (sizeof(tmp) > 2)
    {
	notify_fail("You cannot feed "+ COMPOSITE_WORDS(tmp[1..]) +
	    "all at the same time.\n");
	return 0;
    }

    return steed_do_feed(food, this_player());
}

