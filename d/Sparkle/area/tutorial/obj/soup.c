/*
 *  /d/Sparkle/area/tutorial/obj/soup.c
 *
 *  This is a lower level food item from the Greenhollow
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
    set_name("soup");
    add_name("bowl");
    add_adj( ({ "hot", "onion" }) );
    set_pname("bowls of onion soup");

    set_short("bowl of onion soup");
    set_long("This soup is a fairly small meal. You would"
      + " have to <eat> quite a few of them before you were"
      + " full. Being full helps you recover from fatigue"
      + " more quickly.\n");

    add_prop(OBJ_I_VALUE, 0);
   set_amount(40);
} /* create_food */
