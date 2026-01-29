/*
 *	/d/Gondor/minas/s2crc3.c
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
    set_circle("Third");
    set_streetname("Tolfalas Street");
    set_areaname("southern");
    set_streettype("narrow street");
    set_activity(1);
    set_wealth(1);
    add_exit(MINAS_DIR + "s1crc3", "northeast", 0, 1);
    add_exit(MINAS_DIR + "s3crc3", "west",      0, 1);
    add_exit(MINAS_DIR + "rooms/wtpub","south", 0, 0);
    set_extraline("The street continues west, and northeast you " +
	"can see the doors of the Fourth Gate, which leads through " +
	"the Fourth Wall north of here.");

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
