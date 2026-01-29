/*
 *  /d/Emerald/telberin/obj/oats.c
 *
 *  This is the lowest level food item from the Inn in
 *  Telberin in Emerald.
 *
 *  Copyright (c) April 2003, by Cooper Sherry (Gorboth)
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
    add_name( ({ "cup", "_sparkle_tour_food" }) );
    add_adj( ({ "warm", "creamed" }) );
    set_pname("cups of warm porridge");

    set_short("cup of creamed oats");
    set_long("Served in an elegant wooden cup with a handle,"
      + " this warm batch of creamed oats smells quite excellent."
      + " Steam rising from the bowl smells of nutmeg and perhaps"
      + " a few raisins which have been added for flavor.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_amount(55);
    add_prop(OBJ_I_WEIGHT,70);
    add_prop(OBJ_I_VOLUME,76);
} /* create_food */
