/*
 *  /d/Sparkle/area/tutorial/obj/duck.c
 *
 *  This is an upper-level food item from the Inn in
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
    set_name("duck");
    add_name("bird");
    add_name("plate");
    set_pname("plates of roasted duck");
    add_adj( ({ "hot", "roast", "roasted" }) );

    set_short("plate of roasted duck");
    set_long("This is very large meal. It won't take too many"
      + " meals like this to fill you up completely. You can"
      + " <eat> this food to increase how full you are. When"
      + " you are full, you recover from fatigue more quickly.\n");
    add_prop(OBJ_I_VALUE, 0);
    set_amount(74);
} /* create_food */
