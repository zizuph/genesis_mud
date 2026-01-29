/*
 *  /d/Sparkle/area/tutorial/obj/venison.c
 *
 *  This is the top level food item from the Greenhollow
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
    set_name("venison");
    add_name("filet");
    add_name("meat");
    add_name("steak");
    set_pname("filets of venison");
    add_adj( ({ "filet", "of" }) );

    set_short("filet of venison");
    set_long("What a huge meal! You might not even be able"
      + " to eat this much until you grow in size. If you"
      + " can <eat> it, it won't take very many of this"
      + " type of food to make you completely full. When you"
      + " are full, you recover more quickly from fatigue.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_amount(100);
} /* create_food */
