/*
 *	/d/Gondor/minas/n1crc4.c
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
inherit "/d/Gondor/minas/lib/std_ogate.c";

#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

#define MT_I_GAVE_PASSWORD	"_MT_i_gave_password"

public void
create_street()
{
    set_circle("Fourth");
    set_streetname("Main Street");
    set_areaname("north-eastern");
    set_streettype("broad street");
    set_activity(2);
    set_wealth(1);
    add_exit(MINAS_DIR + "e3crc4", "southeast",               0, 1);
    add_exit(MINAS_DIR + "gate5",  "southwest", "@@pass_gate@@", 1);
    add_exit(MINAS_DIR + "n2crc4", "northwest",               0, 1);
    set_extraline("Before you to the southwest lies the Fifth Gate, which leads "+
        "through to the Fifth Circle beyond the wall. The Main Street continues "+
        "southeast, and a narrower street to the northwest. ");
    add_item(({"gates","fifth gate","gate"}), BSN(
        "This is the Fifth Gate that guards the City. The gates are closed, "+
        "and you will not get through without a password."));
    add_item("wall", BSN(
        "The Fifth wall surrounds the inner parts of Minas Tirith to the "+
        "southwest, and the Fifth Gate leads through it."));

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

