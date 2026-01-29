/*
 *  /d/Sparkle/guilds/new_merc/obj/finest.c
 *
 *  This is the high level drink item from the Mess Hall of the Mercenary
 *  Guild.
 *
 *  Sold at: /d/Sparkle/guilds/new_merc/rooms/mess_hall.c
 *
 *  Created June 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/drink";

#include <stdproperties.h>

/* Prototypes */
public void        create_drink();

/*
 * Function name:        create_drink
 * Description  :        set up the drink object
 */
public void
create_drink()
{
    set_name("finest");
    add_name( ({ "shot", "liquor", "whiskey", "bourbon" }) );
    add_adj( ({ "shot", "of", "sparkle", "sparkles", "sparkle's",
                "single-malt" }) );

    set_short("shot of Sparkle's Finest");
    set_pshort("shots of Sparkle's Finest");
    set_long("Sparkle's Finest is a widely reknown single-malt"
      + " whiskey crafted by the masters in the city. It has a light"
      + " amber coloring, and awakens everything it touches on the"
      + " way down. The flavor is simply perfection.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_soft_amount(60);
    set_alco_amount(45);
    add_prop(OBJ_I_WEIGHT, 60);
    add_prop(OBJ_I_VOLUME, 60);
} /* create_drink */
