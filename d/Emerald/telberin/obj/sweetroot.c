/*
 *  /d/Emerald/telberin/obj/sweetroot.c
 *
 *  This is the mid-level food item from the Inn in
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
    set_name("sweetroot");
    add_name("root");
    add_adj( ({ "baked", "sweet" }) );

    set_short("baked sweetroot");
    set_long("Sweetroot is a large starchy food grown in"
      + " the southern areas of Emerald. Similar to a"
      + " potato in texture, it is much sweeter, and"
      + " narrower in shape. This one has been baked to"
      + " perfection and served with a pad of butter and"
      + " sprig of parsley.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_amount(150);
    add_prop(OBJ_I_WEIGHT,160);
    add_prop(OBJ_I_VOLUME,140);
} /* create_food */
