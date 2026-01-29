/*
 *	/d/Gondor/minas/s1crc5.c
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
inherit "/d/Gondor/minas/lib/std_ogate";

#include <macros.h>
#include "/d/Gondor/std/tell.c"

#include "/d/Gondor/defs.h"

#define MT_I_GAVE_PASSWORD	"_MT_i_gave_password"

public void
create_street()
{
    set_circle("Fifth");
    set_streetname("Main Street");
    set_areaname("south-eastern");
    set_streettype("broad street");
    set_activity(2);
    set_wealth(2);
    add_exit(MINAS_DIR + "s2crc5", "southwest", 0, 1);
    add_exit(MINAS_DIR + "e1crc5", "northeast", 0, 1);
    add_exit(MINAS_DIR + "gate6",  "northwest", "@@pass_gate@@", 1);
    set_extraline("Before you to the northwest lies the Sixth Gate, which leads "+
    "through to the Sixth Circle beyond the wall. The Main Street continues "+
    "northeast, and a narrower street to the southwest. ");
    add_item(({"gates","sixth gate","gate"}), BSN(
    "This is the Sixth Gate that guards the City. The gates are closed, "+
    "and you won't get through without a password."));
    add_item("wall", BSN(
    "The Sixth wall surrounds the inner parts of Minas Tirith to the "+
    "southwest, and the Sixth Gate leads through it."));

    /* These items are similar in all streets on all levels */

    add_street_items();

    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    reset_room();

}

public void
init()
{
    ::init();

    init_gate();
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (ob->query_prop(MT_I_GAVE_PASSWORD) &&
	ENV(ob) != TO)
    {
	ob->remove_prop(MT_I_GAVE_PASSWORD);
	TO->close_gate();
    }
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

