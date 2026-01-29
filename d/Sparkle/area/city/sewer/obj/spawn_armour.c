/*
 * /w/aeg/sparkle/sewer/obj/spawn_armour.c
 *
 * This is the armour that some gremlins will wear. It is intended
 * to cover the whole body and provide AC with a focus on slash
 * defense. It is a slippery mess.
 *
 * Created 10 FEB 2009, by Aeg (Matthew Morin)
 */
#pragma strict_types

inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include "../defs.h"

public void
create_armour()
{
    set_name("ooze");
    add_name("spawning ooze", "green ooze");
    add_adj("spawning");
    add_adj("green");
    set_short("green spawning ooze");
    set_long("This ooze smells like a combination of rotting fish and sour "
        + "milk. It is the colour of a mix of a dying man's snot and mouldy "
        + "bread.\n");
        
    set_ac(12 + random(2));
    set_at( A_BODY | A_ARMS | A_LEGS | A_HEAD );
    set_am(({ 0, 2, 0 }));
    
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 15000);
    add_prop(OBJ_M_NO_SELL, 1);
}


/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (!dest->query_race_name("gremlin"))
    {
        tell_room(dest, "The ooze sizzles and evaporates as it"
          + " hits the ground!\n");
        remove_object();
    }
} /* enter_env */
