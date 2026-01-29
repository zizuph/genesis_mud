/*
 * Rolling pin for mother on level 2
 * - Boreaulam, Sep 2012
 */
#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

/*
 * Function name:        create_weapon
 * Description  :        constructor for the object
 */
void
create_weapon()
{

    set_name("rolling-pin");
    set_adj("big");
    set_adj("wooden");
    set_short("big wooden rolling-pin");
    set_long("The rolling pin is a cylindrical food preparation utensil " +
        "used to shape and flatten dough. You might also be able to " +
        "improvise and use it as a cudgel.\n");

    set_hit(20 + random (5));
    set_pen(15 + random (5));
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);

    add_prop(OBJ_I_WEIGHT,5500);
    add_prop(OBJ_I_VOLUME,4500);

    set_hands(W_ANYH);
} /* create_weapon */

