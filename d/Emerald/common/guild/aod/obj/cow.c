/*
 *  /d/Emerald/common/guild/aod/obj/cow.c
 *
 *  This is the mid level food item from the Mess Hall of the Army of
 *  Darkness.
 *
 *  Sold at: /d/Emerald/common/guild/aod/rooms/mess_hall.c
 *
 *  Created November 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/food";
inherit "/d/Emerald/common/guild/aod/lib/ogre_food";

#include <stdproperties.h>

/* Prototypes */
public void        create_food();

/*
 * Function name:        create_food
 * Description  :        set up the food object
 */
public void
create_food()
{
    set_name("cow");
    add_name("stick");
    add_name("meat");
    set_pname("cows on a stick");
    add_adj( ({ "on", "a" }) );

    set_short("cow on a stick");
    set_pshort("cows on a stick");
    set_long("An entire cow has been skewered on a long, sharp pole,"
      + " rolled in batter, breaded, and then deep fried in a giant"
      + " cauldron of oil! How this could have possibly been done without"
      + " the help of thirteen men, one can only imagine. I suppose if"
      + " you had an ogre in the kitchen it wouldn't be all that"
      + " far fetched.\n");

    add_ogre_food_props();

    add_item( ({ "cow on a stick" }), long);

    add_prop(OBJ_I_VALUE, 0);
    set_amount(285);
    add_prop(OBJ_I_WEIGHT, 285);
    add_prop(OBJ_I_VOLUME, 200);
} /* create_food */
