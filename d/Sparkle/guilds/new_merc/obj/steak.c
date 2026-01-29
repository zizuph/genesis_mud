/*
 *  /d/Sparkle/guilds/new_merc/obj/steak.c
 *
 *  This is the high level food item from the Mess Hall of the Mercenary
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
    set_name("steak");
    add_name("filet");
    add_name("meat");
    add_name("beef");
    add_adj( ({ "16-oz", "16-oz.", "oz" }) );

    set_short("16-oz steak");
    set_long("What a mouth watering sight! 16 ounces of"
      + " prime beef have been cut into a thick"
      + " steak and grilled to perfection. The inner layers"
      + " are red and juicey, and the meat almost melts in your"
      + " mouth. A more flavorful meal than this is hard to find.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_amount(560);
    add_prop(OBJ_I_WEIGHT,550);
    add_prop(OBJ_I_VOLUME,540);
} /* create_food */