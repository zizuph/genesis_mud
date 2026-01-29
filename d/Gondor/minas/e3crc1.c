/*
 *	/d/Gondor/minas/e3crc1.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	28-Jan-1997, Olorin:	Changed inheritance,
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
    set_circle("First");
    set_areaname("eastern");
    set_streetname("Lampwrights' Street");
    set_streettype("street");
    set_activity(1);
    set_wealth(2);
    add_exit(MINAS_DIR + "wall/ninwall1", "east",      0, 1);
    add_exit(MINAS_DIR + "gate1",         "south",     0, 1);
    add_exit(MINAS_DIR + "rooms/mttransport", "west",  0, 0);
    add_exit(MINAS_DIR + "n1crc1",        "northwest", 0, 1);

    set_extraline("The street is narrower to the northwest, but " +
	"to the south it widens out to a square behind the First " +
        "Gate of the city. To the east is a guard barrack.");

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


