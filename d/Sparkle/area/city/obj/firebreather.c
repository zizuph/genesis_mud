/*
 *  /d/Sparkle/area/city/obj/firebreather.c
 *
 *  This is the highest level drink item from the Boar's Head
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
    set_name("firebreather");
    add_name( ({ "spirit" }) );

    set_short("firebreather");
    set_long("Throat scorcher and cauterizer of of intestines, this"
      + " spirit is the real deal. It is called the \"firebreather\""
      + " for a reason. No need to hesitate - bottoms up!\n");

    add_prop(OBJ_I_VALUE, 0);
    set_soft_amount(50);
    set_alco_amount(50);
    add_prop(OBJ_I_WEIGHT, 75);
    add_prop(OBJ_I_VOLUME, 75);
} /* create_drink */