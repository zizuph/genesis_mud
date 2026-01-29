/*
 * File:     Candle
 * Created:  Cirion, 1998.06.02
 * Purpose:  candle that, when lit by the Jazur Flame and
 *           placed in the lanthorn at  
 *           ~Avenir/union/room/lanthorn_room,
 *           will open a passageway.
 *           Will also re-ignite the Flame if it is lighted.
 *
 * Revisions:
 * 	Lucius, Jul 2017: Re-Code. Removed as Firestarter.
 */
#pragma strict_types

inherit "/std/torch";
#include <stdproperties.h>
#include <macros.h>

#include "../defs.h"

public void 
create_torch()
{
    set_name("candle");
    add_name("jazur_candle");
    set_short("small blue candle");
    add_adj (({"small", "blue", "wax" }));
    add_adj("union");

    set_long ("Made from soft blue wax, this short, wide candle "
      + "seems to be designed to be set within a lantern. The "
      + "wick is very stiff and made from some very strong "
      + "cord material.\n");

    set_time(500);
    set_strength(5);
    set_value(130 + random(25));
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 50);

    if (IS_CLONE)
      set_item_expiration(); 
}

/*
 * Function name: query_light_fail
 * Description:   hook to see if we can light the torch or not.
 * Returns:       something other than  0 if lighting failed.
 */
public mixed
query_light_fail()
{
    mixed res;
    object where = TO;

    // callback to see if we fail some other way
    res = ::query_light_fail ();

    if (res)
	return res;

    // the candle can only be lit from the Jazur Flame...
    while (objectp(ENV(where))) // get the top level room from this object
	where = ENV(where);

    res = where->query_jazur_flame_present();

    if (stringp(res))
	return res;

    if (!res)
	return "It refuses to catch flame.\n";

    write ("You hold the candle to the dark fire, and it "+
	"seems to gather folds of the flame into itself.\n");

    return 0;
}

/*
 * Function name: query_holds_jazur_flame
 * Description:   Check to see if this object holds the
 *                Jazur flame
 * Arguments:     none
 * Returns:       1 if it holds the flame
 */
public int
query_holds_jazur_flame()
{
    return !!query_lit(0);
}

/*
 * Function name: burned_out
 * Description:	  If this function is called when the torch has burned out.
 */
public void
burned_out()
{
    object env = environment();

    if (env->query_prop("is_jazur_lanthorn"))
    {
	tell_room(environment(env), "The candle in the "+
	    "lanthorn gutters and goes out.\n", env);
	environment(env)->catch_lanthorn_lost_flame();
    }
    ::burned_out();
}


public void
appraise_object(int num)
{
    ::appraise_object(num);

}

public string
query_recover(void)
{
    return MASTER + ":" + query_item_expiration_recover();
}

public void
init_recover(string arg)
{
    init_item_expiration_recover(arg);

}
