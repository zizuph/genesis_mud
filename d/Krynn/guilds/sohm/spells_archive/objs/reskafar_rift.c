/* creator(s):  Arman 2019
 *
 * Based on Sparkle trash can
 */
#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <composite.h>
#include <cmdparse.h>
    

public void
create_container()
{
    add_adj("dimensional");
    set_name("rift"); 
    set_long("Before you is a small magical rift in the fabric of space " +
        "and time, a pocket dimension that sits between the Material " +
        "Plane of your reality and the Elemental Planes of raw elemental " +
        "matter and energy. Chaotic waves of chromatic light and energy " +
        "dizzy you as you try and make out further details beyond the rift.");

    add_prop(OBJ_M_NO_GET, "Your hand passes through the dimensional rift as " +
        "you try and grab it.\n");
    add_prop(OBJ_I_VALUE,  0); 
    add_prop(CONT_I_WEIGHT, 0);    // 1500 kilos
    add_prop(CONT_I_VOLUME, 0);      // 40 litres
    add_prop(CONT_I_MAX_VOLUME, 90000);  // 90 litres
    add_prop(CONT_I_MAX_WEIGHT, 2500000); // 250 kilos
    add_prop(CONT_I_RIGID, 0);

    add_prop(MAGIC_AM_ID_INFO, ({ "This is a magical rift between the planes, " +
        "called in to being by a Wizard of considerable ability.\n", 25 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));
}

void
enter_inv(object obj, object from)
{
/*
    if (living(obj))
    {
	write("You cannot put living creatures into the rift!\n");
	return;
    }
*/
    ::enter_inv(obj,from);
}

void
leave_inv(object obj, object to)
{
    ::leave_inv(obj,to);
}

/*
 * Function name: describe_contents
 * Description:   Give a description of items in this container
 * Arguments:     object for_obj - To whom to give the description
 *                object *obarr  - The items to describe
 */
public void
describe_contents(object for_obj, object *obarr)
{
    for_obj->catch_tell(show_sublocs(for_obj));

    if (sizeof(obarr) > 0)
    {
        for_obj->catch_tell(" Floating within the rift you can " +
            "see " + COMPOSITE_DEAD(obarr) + ".\n");
    }
    else
    {
        for_obj->catch_tell("\n");
    }
}