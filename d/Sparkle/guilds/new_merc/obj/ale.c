/*
 *  /d/Sparkle/guilds/new_merc/obj/ale.c
 *
 *  This is the low level drink item from the Mess Hall of the Mercenary
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
    set_name("ale");
    add_name( ({ "pint", "glass", "beer" }) );
    add_adj( ({ "pint", "of", "barley" }) );

    set_short("pint of barley ale");
    set_pshort("pints of barley ale");
    set_long("Ah, excellent! When it comes to wanting to relax with a bit"
      + " of flavor to quench your thirst, it is hard to do much better"
      + " than this sort of barley ale. Light hops combine with a rich"
      + " malty aroma that hints at fresh-baked bread. Simply"
      + " delicious!\n");

    add_prop(OBJ_I_VALUE, 0);
    set_soft_amount(270);
    set_alco_amount(8);
    add_prop(OBJ_I_WEIGHT, 270);
    add_prop(OBJ_I_VOLUME, 270);
} /* create_drink */
