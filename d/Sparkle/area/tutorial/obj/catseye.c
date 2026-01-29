/*
 *  /d/Sparkle/area/tutorial/obj/cats_eye.c
 *
 *  This is the super-loot item found on lions in the Tutorial
 *  Area. It is intended as a moneymaker and is relatively rare
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
    set_name("eye");
    add_name("_tutorial_item");

    set_short("shining cats eye");
    add_adj( ({ "shining", "cat", "cats" }) );

    set_long("Though often found on corpses of mountain lions in the"
      + " mountains of Silverdell, no one is sure exactly what a"
      + " cats eye is. They are not a literal eye, but rather a stone"
      + " of some kind that the cats somehow carry with them. They are"
      + " rare and very valuable. You should sell it in town.\n");

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 30);
    add_prop(OBJ_I_VALUE, 300 + random(100));
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
        return "You cannot steal from a wild animal!\n";
    }

    return 0;
} /* check steal */



