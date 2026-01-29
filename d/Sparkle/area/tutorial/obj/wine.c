/*
 *  /d/Sparkle/area/tutorial/obj/wine.c
 *
 *  This is the mid-level alcohol in Silverdell.
 *
 *  Sold at: /d/Sparkle/area/tutorial/town/tavern.c
 *
 *  Created June 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
inherit "/std/drink";

#include <stdproperties.h>

/*
 * Function name:        create_drink
 * Description  :        set up the drink
 */
public void
create_drink()
{
    set_name("wine");
    add_name( ({ "alcohol" }) );
    set_adj("barley");
    add_name("bottle");

    set_short("bottle of barley wine");
    set_pshort("bottles of barley wine");
    set_long("This is a bottle of barley wine. You can <drink>"
      + " it to become intoxicated. The drunker you are, the"
      + " faster you heal after combat. It won't take too many"
      + " of these to get you completely drunk.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_soft_amount(1); /* let them drink as much as they can */
    set_alco_amount(6);
    add_prop(OBJ_I_WEIGHT,30); /* we don't want to burden the */
    add_prop(OBJ_I_VOLUME,30); /* newbies too much, do we?    */
} /* create_drink */
