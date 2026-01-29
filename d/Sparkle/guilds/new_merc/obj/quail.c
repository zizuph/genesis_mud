/*
 *  /d/Sparkle/guilds/new_merc/obj/quail.c
 *
 *  This is the mid level food item from the Mess Hall of the Mercenary
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
    set_name("quail");
    add_name("bird");
    add_name("plate");
    add_adj( ({ "hot", "roast", "roasted" }) );

    set_short("plate of roasted quail");
    set_pshort("plates of roasted quail");
    set_long("The flesh of this roast quail has been just"
      + " slightly blackened along the sides to allow for"
      + " a crisp outer layer. Juices and oils have pooled"
      + " beneath the bird along with healthy doses of"
      + " sauce which have been poured over the meat to mix"
      + " with a few root vegetables that are served alongside. It"
      + " smells simply divine.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_amount(350);
    add_prop(OBJ_I_WEIGHT,350);
    add_prop(OBJ_I_VOLUME,300);
} /* create_food */