/*
 *  /d/Sparkle/area/tutorial/obj/ale.c
 *
 *  This is the low-level alcohol in Greenhollow.
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
    set_name("ale");
    add_name( ({ "beer", "alcohol", "amber" }) );
    set_adj("amber");
    add_name("mug");

    set_short("mug of amber ale");
    set_pshort("mugs of amber ale");
    set_long("This is a mug of amber ale. You can <drink>"
      + " it to get intoxicated. The drunker you are, the"
      + " faster you heal after combat. It will take quite"
      + " a few of these to get you completely drunk.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_soft_amount(1); /* let them drink as much as they can */
    set_alco_amount(3);
    add_prop(OBJ_I_WEIGHT,30); /* we don't want to burden the */
    add_prop(OBJ_I_VOLUME,30); /* newbies too much, do we?    */
} /* create_drink */
