/*
 *  /d/Sparkle/area/tutorial/obj/fang.c
 *
 *  This is the super-loot item found on animals in the Sterling
 *  Forest. It is intended as a moneymaker and is relatively rare
 *  random loot.
 *
 *  Created December 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
inherit "/std/object";

#include <ss_types.h>
#include <stdproperties.h>

/* prototypes */
public void        create_object();
public mixed       check_steal();


/*
 * Function name:        create_object
 * Description  :        set up the rabbit foot
 */
public void
create_object()
{
    set_name("fang");
    add_name("_tutorial_item");

    set_short("glittering animal fang");
    add_adj( ({ "glittering", "animal" }) );

    set_long("This fang, obviously taken from a large animal, is lustrous"
      + " and very beautiful. Objects like this are prized in Greenhollow"
      + " for their use in jewelry. You could probably sell it for a"
      + " fair price in town.\n");

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 30);
    add_prop(OBJ_I_VALUE, 150 + random(100));
    add_prop(OBJ_M_NO_STEAL, check_steal);

} /* create_object */


/*
 * Function name:        check_steal
 * Description  :        this foot should not be stolen from the
 *                       animal who owns it (duh)
 * Returns      :        1: cannot steal
 *                       0: okay to steal
 */
public mixed
check_steal()
{
    if (!living(environment(this_object())))
    {
        return 0;
    }

    if (environment(this_object())->id("_tutorial_animal"))
    {
        return "Live animals do not typically give up their fangs.\n";
    }

    return 0;
} /* check steal */



