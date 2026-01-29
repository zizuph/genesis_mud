/*
 *	/d/Gondor/minas/e1crc2.c
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
    set_circle("Second");
    set_streetname("Main Street");
    set_areaname("eastern");
    set_streettype("street");
    set_activity(1);
    set_wealth(1);
    add_exit(MINAS_DIR + "e2crc2",         "north",     0, 1);
    add_exit(MINAS_DIR + "rooms/mttavern", "east",      0, 0);
    add_exit(MINAS_DIR + "gate2",          "southwest", 0, 1);
    
    set_extraline("The street continues north and southwest, " +
	"following the circle of the Second Wall to the east, " +
        "and the Third Wall to the west. To the east is the " +
        "entrance of the Sword and Shield Tavern, and to the " +
	"southwest is the Second Gate.");
    add_item("wall", "The walls that surround the seven levels " +
	"of Minas Tirith are built strong to make the city an " +
        "impenetrable fortress.\n");

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

