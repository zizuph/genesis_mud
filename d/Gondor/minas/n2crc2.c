/*
 *	/d/Gondor/minas/n2crc2.c
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
    set_circle("Second");
    set_streetname("Anorien Street");
    set_streettype("narrow street");
    set_areaname("northern");
    set_activity(1);
    set_wealth(1);
    add_exit(MINAS_DIR + "houses/wqhouse1", "north",     0, 0);
    add_exit(MINAS_DIR + "n1crc2",          "southeast", 0, 1);
    add_exit(MINAS_DIR + "n3crc2",          "west",      0, 1);
    set_extraline("The narrow street continues southeast towards " +
	"the Third Gate, and west, where it seems to end in a narrow alley.");

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


