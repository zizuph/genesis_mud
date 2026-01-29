/*
 *  /d/Sparkle/guilds/new_merc/obj/jerky.c
 *
 *  This is the low level food item from the Mess Hall of the Mercenary
 *  Guild.
 *
 *  Sold at: /d/Sparkle/guilds/new_merc/rooms/mess_hall.c
 *
 *  Created June 2009, by Cooper Sherry (Gorboth)
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
    set_name("jerky");
    add_name( ({ "meat", "cord", }) );
    add_adj( ({ "cord", "cords", "of", "dried", "meat", }) );

    set_short("cord of dried meat jerky");
    set_pname("cords of dried meat jerky");
    set_long("Long stips of meat (venison, mostly) have been dipped in"
      + " some flavorful sauce, and then dried in a smokehouse for many"
      + " hours to produce these cords of jerky. Though a bit tough"
      + " to chew, they have an excellent spicy flavor and offer some"
      + " protein for the road.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_amount(55);
    add_prop(OBJ_I_WEIGHT,40);
    add_prop(OBJ_I_VOLUME,40);
} /* create_food */