/*
 *  /d/Sparkle/area/city/obj/water.c
 *
 *  A simple glass of water which can be purchased from the Boar's Head
 *  Tavern in Sparkle.
 *
 *  Sold at : /d/Sparkle/area/city/rooms/inside/sparkle_pub.c
 *
 *  Created August 2018, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/drink";

#include <stdproperties.h>

/* Prototypes */
public void        create_drink();

/*
 * Function name:        create_drink
 * Description  :        set up the drink object
 */
public void
create_drink()
{
    set_name("water");
    add_name( ({ "mug" }) );

    set_short("mug of water");
    set_pshort("mugs of water");
    set_long("A mug of ... water. It quenches the thirst just fine,"
      + " but doesn't exactly put anyone in a better mood. Enjoy?\n");

    add_prop(OBJ_I_VALUE, 0);
    set_soft_amount(100);
    set_alco_amount(0);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
} /* create_drink */
