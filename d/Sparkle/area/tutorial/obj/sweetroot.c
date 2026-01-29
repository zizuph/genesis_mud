/*
 *  /d/Sparkle/area/tutorial/obj/sweetroot.c
 *
 *  This is the mid-level food item from the Inn in
 *  Greenhollow.
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
    set_name("sweetroot");
    add_name("root");
    add_adj( ({ "baked", "sweet" }) );

    set_short("baked sweetroot");
    set_long("This meal is a fair portion of food. You'll"
      + " probably have to <eat> a few of them before you"
      + " feel completely full. When you are full, you"
      + " recover from fatigue more quickly.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_amount(60);
} /* create_food */
