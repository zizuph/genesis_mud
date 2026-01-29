/*
 *  /d/Sparkle/area/city/obj/wine.c
 *
 *  This is the basic level drink item from the Boar's Head Tavern
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
    set_name("wine");
    add_name( ({ "cup" }) );
    add_adj( ({ "cup", "of", "red" }) );

    set_short("cup of red wine");
    set_pshort("cups of red wine");
    set_long("Served in a dented metal cup, this wine looks ... well"
      + " it looks like the sort of thing you would expect to get"
      + " in a pub between warehouses on a dock filled with"
      + " sailors who aren't too picky. It is a generic red, and will"
      + " certainly wet your throat with a bit of sour flavour.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_soft_amount(75);
    set_alco_amount(16);
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 80);
} /* create_drink */