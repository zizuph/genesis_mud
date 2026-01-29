/*
 *	/d/Gondor/minas/e3crc5.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	29-Jan-1997, Olorin:	Changed inheritance,
 *				general revision.
 *  Last modified by Alto, 09 June 2001
 *      Added room tells and revised descriptions
 */
#pragma strict_types

inherit "/d/Gondor/minas/lib/street.c";
inherit "/d/Gondor/minas/lib/street_funcs.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

public void
create_street()
{
    set_circle("Fifth");
    set_streetname("Main Street");
    set_areaname("eastern");
    set_streettype("broad street");
    set_activity(1);
    set_wealth(1);
    add_exit(MINAS_DIR + "tcrc5", "south",     0, 1);
    add_exit(MINAS_DIR + "gate5", "northwest", 0, 1);
    set_extraline("The street continues north, where you can see the doors of "
      + "the Fifth Gate, which leads out to the Fourth Circle. South, the "
      + "Main Street runs through a tunnel piercing the mountain-leg which "
      + "divides the City in two parts.");

    /* These items are similar in all streets on all levels */

    add_street_items();

    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    reset_room();

}

/*
 * This function enables the random room tells.
 */

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

