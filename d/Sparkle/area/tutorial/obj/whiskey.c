/*
 *  /d/Sparkle/area/tutorial/obj/whiskey.c
 *
 *  This is the upper-level alcohol in Silverdell.
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
    set_name("whiskey");
    add_name( ({ "alcohol", "shot", "glass" }) );
    set_adj("small");

    set_short("small shot of whiskey");
    set_pshort("small shots of whiskey");
    set_long("This is a small shot of whiskey. You can <drink>"
      + " it to become intoxicated. The drunker you are, the"
      + " faster you heal after combat. This might be too strong"
      + " for you to drink at all. If not, it won't take more"
      + " than one or two to get you completely drunk.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_soft_amount(1); /* let them drink as much as they can */
    set_alco_amount(12);
    add_prop(OBJ_I_WEIGHT,30); /* we don't want to burden the */
    add_prop(OBJ_I_VOLUME,30); /* newbies too much, do we?    */
} /* create_drink */
