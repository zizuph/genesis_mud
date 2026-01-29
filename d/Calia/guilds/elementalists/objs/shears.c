/*
 *  Pruning shears for Tending the Garden
 *
 *  Players can use these shears, found in the shed, to tend the garden.
 *
 *  Created May 2011 by Petros
 */
#pragma strict_types

inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>


/*
 * Function name:        create_weapon
 * Description  :        set up the weapon
 */
public void
create_weapon()
{
    set_name("secateur");
    add_name("_elementalist_garden_secateur");
    add_name( ({ "shears", "pruning shears" }) );
    add_adj( ({ "black-handled", "sturdy" }) );

    set_short("black-handled sturdy secateur");
    set_long("This is a secateur, also known as pruning shears.\n");

    add_prop(OBJ_M_NO_SELL, "The " + short() + " cannot be sold.\n");

    set_default_weapon(5, 5, W_KNIFE, W_SLASH|W_IMPALE, W_BOTH, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(5, W_KNIFE));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(5, 5));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

    set_may_not_recover();
}
