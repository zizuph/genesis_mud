/*
 * /d/Shire/obj/oil_flask.c
 * When empty, flask decays. Based on /std/torch which falls apart when empty.
 * By Finwe, March 2005
 */

inherit "/d/Gondor/common/obj/oilflask";

inherit "/std/object.c";
inherit "/lib/keep.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Shire/sys/defs.h"
#define DECAY_TIME (300.0)

static  int Decay_Alarm;        /* Alarm used when the flask decays */

void create_object()
{
    set_name("oil");
    add_adj(({"flask", "large"}));
    add_adj("oil");
    add_name("flask");
    add_name("oil-flask");
    add_name("lamp-oil");
    add_name("_gondorian_flask_with_oil_");

    set_pname("flasks");
    add_pname("oil-flasks");

    add_adj("lamp");

    set_short(short_description);
    set_pshort(pshort_description);
    set_long(long_description);

    set_amount(6000);

    add_prop(OBJ_I_VALUE,  compute_value);
    add_prop(OBJ_I_WEIGHT, compute_weight);
    add_prop(OBJ_I_VOLUME, compute_volume);
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
void
decay_item()
{
    object env = environment();
    string tmp = short();

    if (living(env))
    {
	tell_object(env, "The remains of the " + tmp + " fall apart.\n");
	tell_room(environment(env), "The remains of the " + tmp + " that " +
	    QTNAME(env) + " is holding fall apart.\n", env);
    }
    else if (env->query_prop(ROOM_I_IS))
    {
	tell_room(env, "The remains of the " + tmp + " fall apart.\n");
    }

    remove_object();
}

void
remove_oil(int i)
{
    oil_amount -= i;

    if (oil_amount <= 0)
    {
        oil_amount = 0;
        add_adj("empty");
        Decay_Alarm = set_alarm(DECAY_TIME, 0.0, decay_item);
    }
}


string
short_description()
{
    if (!oil_amount)
    {
        return "empty oil-flask";
    }

    return "flask of oil";
}

string
pshort_description()
{
    if (!oil_amount)
    {
        return "empty oil-flasks";
    }

    return "flasks of oil";
}

string
long_description()
{
    string long_desc = "It is an oil-flask imported from Waterdeep. The flask is made of clear glass and designed to hold lamp-oil for an oil-lamp. ";

    if (!oil_amount)
    {
        long_desc += "The flask is empty. ";
    }
    else
    {
        long_desc += "The flask contains some oil. ";
    }

    if (query_keep())
    {
        long_desc += "Presently, you do not want to sell the flask.";
    }
    else
    {
        long_desc += "If you do not want to sell the flask, just decide to " +
            "<keep flask>.";
    }

    return BSN(long_desc);
}
