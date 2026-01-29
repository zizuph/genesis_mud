/*
 * stick on level 2
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

    set_name("stick");
    set_adj("wooden");
    set_short("wooden stick");
    set_long("The shaft of this plain wooden stick is very smooth, likely " +
        "the treasure of some young boy who might use it as a toy. In an " +
        "emergency, you might be able to use it as a cudgel.\n");

    set_hit(10 + random (5));
    set_pen(10 + random (5));
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);

    add_prop(OBJ_I_WEIGHT,500);
    add_prop(OBJ_I_VOLUME,500);

    set_hands(W_ANYH);
} /* create_weapon */

