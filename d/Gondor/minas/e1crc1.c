/*
 *	/d/Gondor/minas/e1crc1.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	28-Jan-1997, Olorin:	Changed inheritance.
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
    set_streettype("street");
    set_streetname("Main Street");
    set_streetlight(2);
    set_activity(2);
    set_wealth(1);
    add_exit(MINAS_DIR + "e2crc1", "north",     0, 1);
    add_exit(MINAS_DIR + "s1crc1", "southwest", 0, 1);
    set_extraline("The Main Street continues north and southwest from here.");
    add_item("wall", "The First Wall is the strongest wall of the " +
	     "seven that are built around the Citadel.\n");

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


