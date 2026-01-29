/*
 *  /d/Sparkle/area/tutorial/obj/oats.c
 *
 *  This is the lowest level food item from the Greenhollow
 *  Inn.
 *
 *  Sold at: /d/Sparkle/area/tutorial/town/inn.c
 *
 *  Copied with permission from Telberin in Emerald.
 *
 *  Created July 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>

/*
 * Function name:        create_food
 * Description  :        set up the food object
 */
public void
create_food()
{
    set_name("oats");
    add_name("cup");
    add_adj( ({ "warm", "creamed" }) );
    set_pname("cups of warm porridge");

    set_short("cup of creamed oats");
    set_long("These oats are barely a snack. You'll have to"
      + " eat a whole lot of these before you feel full."
      + " Once you are full, you will recover from fatigue"
      + " more quickly.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_amount(20);
} /* create_food */
