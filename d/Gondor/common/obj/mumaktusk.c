/* Modified August 11, 2001 by Serif:
 * set_long changed to allow for varying screen widths;
 * set_long edited slightly for syntax and grammar (standard, archaic
 *    instead of modern, metric);
 * pragma added
 *
 * Tusks now decay after about 60 min. Based on the torch code and to help
 * keep the game a little neater and cleaner.
 -- Finwe March 2006
 */

#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define DECAY_TIME (3480.0)

static  int Decay_Alarm;        /* Alarm used when the tusks decays */
void decay_item();


void
create_object() 
{
    set_name("tusk");
    add_name("ivory");
    add_name("horn");
    set_adj("ivory");
    set_adj("large");
    set_short("large ivory tusk");
    set_pshort("large ivory tusks");
    set_long("This is the large ivory tusk from an adult mumak! The tusk " +
        "is pure white and smooth. The tusk is wrapped with gold chains " +
        "and looks extremely valuable. The tusk is slightly curved, nearly " +
        "twenty feet long, and quite heavy looking.\n");
    
    add_prop(OBJ_I_WEIGHT,40000);
    add_prop(OBJ_I_VOLUME,30000);
    add_prop(OBJ_I_VALUE,7500);

    Decay_Alarm = set_alarm(DECAY_TIME, 0.0, decay_item);

}


/*
 * Function name: query_torch_may_decay
 * Description  : This function will indicate whether the torch may decay or not
 *                after it burns out. By default it returns 1, but if you do not
 *                want to have it decay, you must redefine this function to make
 *                it return 0. This is especially true for oil lamps.
 * Returns      : int 1 - always.
 */
public int
query_torch_may_decay()
{
    return 1;
}


/*
 * Function name: decay_item
 * Description  : This function is called with a delay to destruct the
 *                torch after burning out. Notice that the check for
 *                query_torch_may_decay() must done before calling this
 *                function.
 */
void decay_item()
{
    object env = environment();
    string tmp = short();

    if (living(env))
    {
	tell_object(env, "The " + tmp + " fall apart and disappears.\n");
	tell_room(environment(env), "The " + tmp + " that " +
	    QTNAME(env) + " is holding falls apart and disappears.\n", env);
    }
    else if (env->query_prop(ROOM_I_IS))
    {
	tell_room(env, "The " + tmp + " fall apart and disappears.\n");
    }

    remove_object();
}

void
remove_oil(int i)
{
    Decay_Alarm = set_alarm(DECAY_TIME, 0.0, decay_item);

}
