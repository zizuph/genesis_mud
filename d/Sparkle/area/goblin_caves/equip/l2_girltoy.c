/*
 * toy on level 2
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

    set_name("doll");
    add_name("toy");
    set_adj("wooden");
    add_adj("toy");
    set_short("wooden toy doll");
    set_long("This wooden doll has been crudely carved from wood, with " +
        "awkward looking arms and legs that are too rounded to look " +
        "realistic. If you grabbed the doll by the legs, you might " +
        "be able to swing it around like a club.\n");

    set_hit(5 + random (5));
    set_pen(5 + random (5));
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);

    add_prop(OBJ_I_WEIGHT,500);
    add_prop(OBJ_I_VOLUME,500);

    set_hands(W_ANYH);
} /* create_weapon */

