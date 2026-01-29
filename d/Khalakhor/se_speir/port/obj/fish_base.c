/*
 * fish_base.c
 *
 * This is a base food object from fish bought from the fishmonger
 * in the village. It's used since some of the fish are initially
 * raw an inedible, though it may be possible to 'cook' them later
 * somehow.
 *
 * Khail - April 18/97
 *
 * Teth - February 27, 1999. Modified to clone a small poison if the
 *        fish is raw. Poison file is /d/Khalakhor/common/poisons/foodp.c
 */

#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>
#include "/d/Khalakhor/sys/paths.h";

static int cooked;

public int query_cooked();

/*
 * Function name: set_amount (MASK)
 * Description  : Sets the amount of food in grams. Masked here
 *                to automatically calculate the minimum value
 *                when the amount is set.
 * Arguments    : a - Amount of food in grams as an integer.
 * Returns      : n/a
 */
public void
set_amount(int a)
{
    ::set_amount(a);
    add_prop(OBJ_I_VALUE, 5 + (a * a) / 600);
}

/*
 * Function name: mod_value
 * Description  : Alters the default value of the fish
 *                as set in the set_amount function. Used
 *                to make pre-cooked or harder to find fish
 *                more expensive as a percent.
 * Arguments    : mod - Integer representing the percent increase.
 * Returns      : n/a
 */
public void
mod_value(int mod)
{
    mixed val;

    val = itof(query_prop(OBJ_I_VALUE));
    val += val * itof(mod) / 100.0;

    add_prop(OBJ_I_VALUE, ftoi(val));
}

public nomask mixed
command_eat()
{
    if (!query_cooked())
    {
        object poison;

        seteuid(getuid());
        poison = clone_object(COM_POISONS + "foodp");
        poison->move(this_player());
        poison->start_poison();
        return ::command_eat();
    }

    return ::command_eat();
}

/*
 * Function name: set_cooked
 * Description  : Simply sets the cooked variable to 'true'.
 * Arguments    : n/a
 * Returns      : 0 - Didn't cook it.
 *                1 - Cooked it.
 */
public int
set_cooked()
{
    if (!cooked)
    {
        cooked = 1;
        return 1;
    }
    return 0;
}

/*
 * Function name: query_cooked
 * Description  : Returns whether the cooked variable is set or not.
 * Arguments    : n/a
 * Returns      : 0 - Not cooked.
 *                1 - Cooked.
 */
public int
query_cooked()
{
    return cooked;
}
