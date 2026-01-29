/*
 *  /d/Emerald/telberin/obj/soup.c
 *
 *  This is a lower level food item from the Inn in
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
    set_name("soup");
    add_name("bowl");
    add_adj( ({ "hot", "onion" }) );
    set_pname("bowls of onion soup");

    set_short("bowl of onion soup");
    set_long("The delicious aroma rising from this bowl of"
      + " onion soup would be enough to scent an entire room"
      + " for hours. A great deal of melted white cheese has"
      + " been added to the broth, along with a round piece"
      + " of dark bread.\n");

    add_prop(OBJ_I_VALUE, 0);
   set_amount(95);
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,92);
} /* create_food */
