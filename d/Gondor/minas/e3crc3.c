/*
 *	/d/Gondor/minas/e3crc3.c
 *
 *	Coded 1992 by Elessar.
 *
 *	Modification log:
 *	29-Jan-1997, Olorin:	Changed inheritance.
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
    set_circle("Third");
    set_streetname("Main Street");
    set_areaname("eastern");
    set_streettype("broad street");
    set_activity(1);
    set_wealth(2);
    add_exit(MINAS_DIR + "tcrc3", "south",     0, 1);
    add_exit(MINAS_DIR + "gate3", "northwest", 0, 1);

    set_extraline("The Main Street leads to the Third Gate to the "
	+ "northwest, and through the tunnel through the huge, "
        + "out-thrust bulk that divides the City, towards the "
        + "Fourth Gate further south.");

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

