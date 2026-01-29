/*
 *  /d/Sparkle/area/city/obj/beer.c
 *
 *  This is the low level drink item from the Boar's Head Tavern
 *  in Sparkle.
 *
 *  Sold at: /d/Sparkle/area/city/rooms/inside/sparkle_pub.c
 *
 *  Created August 2018, by Cooper Sherry (Gorboth)
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
    set_name("beer");
    add_name( ({ "glass", "ale" }) );
    add_adj( ({ "glass", "of", "cold" }) );

    set_short("glass of cold beer");
    set_pshort("glasses of cold beer");
    set_long("Oh, this looks nice and cold! Here's the sort of thing"
      + " one could just sit around and drink all day, especially"
      + " after a bit of hard work or adventuring. Cheers!\n");

    add_prop(OBJ_I_VALUE, 0);
    set_soft_amount(100);
    set_alco_amount(4);
    add_prop(OBJ_I_WEIGHT, 104);
    add_prop(OBJ_I_VOLUME, 104);
} /* create_drink */