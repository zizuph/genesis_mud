/*
 *	/d/Gondor/minas/e3crc2.c
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
    add_exit(MINAS_DIR + "tcrc2",  "south",     0, 1);
    add_exit(MINAS_DIR + "n1crc2", "northwest", 0, 1);
    set_extraline("The street continues south into a tunnel through the "+
        "mountain-bulk, and northwest you see the doors of the "+
	"Third Gate, which leads through the wall that lies to the west.");

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

