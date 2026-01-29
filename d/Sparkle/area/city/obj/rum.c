/*
 *  /d/Sparkle/area/city/obj/rum.c
 *
 *  This is the fairly high level drink item from the Boar's Head
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
    set_name("rum");
    add_name( ({ "flagon" }) );
    add_adj( ({ "flagon", "of" }) );

    set_short("flagon of rum");
    set_pshort("flagons of rum");
    set_long("Any captain who wanted to drink much of this rum would"
      + " need to surrender the wheel of the ship before long. It"
      + " smells intensely of alcohol and tastes like a mixture"
      + " of sour cherries and whiskey.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_soft_amount(90);
    set_alco_amount(36);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
} /* create_drink */