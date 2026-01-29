/*
 *  /d/Emerald/telberin/obj/duck.c
 *
 *  This is an upper-level food item from the Inn in
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
    set_name("duck");
    add_name("bird");
    add_name("plate");
    set_pname("plates of roasted duck");
    add_adj( ({ "hot", "roast", "roasted" }) );

    set_short("plate of roasted duck");
    set_long("The flesh of this roast duck has been just"
      + " slightly blackened along the sides to allow for"
      + " a crisp outer layer. Juices and oils have pooled"
      + " beneath the bird along with healthy doses of"
      + " sauce which have been poured over the meat. It"
      + " smells simply divine.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_amount(350);
    add_prop(OBJ_I_WEIGHT,350);
    add_prop(OBJ_I_VOLUME,300);
} /* create_food */
