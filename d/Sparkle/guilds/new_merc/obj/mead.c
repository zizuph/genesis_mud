/*
 *  /d/Sparkle/guilds/new_merc/obj/mead.c
 *
 *  This is the mid level drink item from the Mess Hall of the Mercenary
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
    set_name("mead");
    add_name( ({ "glass" }) );
    add_adj( ({ "glass", "of", "strong" }) );

    set_short("glass of strong mead");
    set_pshort("glasses of strong mead");
    set_long("Mead, though often considered a commoner's drink, can also"
      + " be crafted to perfection by the right hands. A wine of sorts,"
      + " it has a honey-base that infuses the aroma and flavor of"
      + " the drink with sweetness.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_soft_amount(120);
    set_alco_amount(20);
    add_prop(OBJ_I_WEIGHT, 120);
    add_prop(OBJ_I_VOLUME, 120);
} /* create_drink */
