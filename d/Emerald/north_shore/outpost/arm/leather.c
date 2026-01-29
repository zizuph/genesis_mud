/*
 *    /d/Emerald/north_shore/outpost/arm/leather.c
 *
 *    A basic leather armour for the woodcutters to wear.
 *
 *    Created April 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types


inherit "/std/armour";

#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

/* Prototypes */
public void                create_armour();


/*
 * Function name:                create_armour
 * Description  :                set up the armour
 */
public void
create_armour()
{
    set_name("armour");
    set_short("faded leather armour");
    add_adj( ({ "faded", "leather", "tanned", "well-worn", "worn" }) );
    add_name( ({ "leather", "garment" }) );

    set_long("Thick leather from some beast has been tanned and"
      + " carefully pieced together to make up this well-worn"
      + " protective garment.\n");

    set_ac(9);
    set_at(A_BODY);
    set_am( ({ -2, 2, 1 }) );
    add_prop(OBJ_I_WEIGHT,(800+(random(600))));
    add_prop(OBJ_I_VOLUME,(600+(random(600))));
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(9)+random(25)-10);
} /* create_armour */