/*
 *	/d/Gondor/minas/gate4.c
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
inherit "/d/Gondor/minas/lib/std_gate.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

#include <macros.h>

public void
create_street()
{
    set_circle("Fourth");
    set_streetname("Main Street");
    set_areaname("south-eastern");
    set_streettype("broad street");
    set_activity(2);
    set_wealth(2);
    add_exit(MINAS_DIR + "e1crc4", "northeast",               0, 1);
    add_exit(MINAS_DIR + "s1crc3", "southeast", "@@pass_gate@@", 1);
    add_exit(MINAS_DIR + "s1crc4", "southwest",               0, 1);
    set_extraline("Before you to the southeast lies the Fourth Gate, which leads "+
      "out to the Third Circle beyond the wall. The Main Street continues "+
      "northeast, and a narrower street to the southwest.");
    add_item(({"gates","fourth gate","gate"}), VBFC_ME("exa_gate"));
    add_item("wall", "The Fourth wall surrounds the inner parts of Minas Tirith, "
	     + "and the Fourth Gate leads out through it.\n");
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
