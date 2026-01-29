/*
 *	/d/Gondor/minas/gate3.c
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

public int     gate_closed();
public string  exa_gate();

static object *Guard = allocate(3);

public void
create_street() 
{
    set_circle("Third");
    set_streetname("Main Street");
    set_areaname("north-eastern");
    set_streettype("broad street");
    set_activity(2);
    set_wealth(1);
    add_exit(MINAS_DIR + "n1crc2", "northeast", gate_closed, 1);
    add_exit(MINAS_DIR + "n1crc3", "northwest",           0, 1);
    add_exit(MINAS_DIR + "e3crc3", "southeast",           0, 1);

    set_extraline("Before you to the northeast lies the Third Gate, " +
        "which leads out to the Second Circle beyond the wall. The " +
        "Main Street continues southeast, and a narrower street to the " +
        "northwest.");

    add_item( ({"gates","third gate","gate"}), exa_gate);
    add_item("wall", "The Third wall surrounds the inner parts of Minas " +
	"Tirith to the southwest, and the Third Gate leads through it.\n");
    /* These items are similar in all streets on all levels */

    add_street_items();

    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    reset_room();
}

public int
gate_closed() 
{
    switch (tod())
    {
    case "evening":
    case "night":
    case "early morning":
	write("A guard says: The gate is usually closed at night, but...ok.\n"
	    + "He opens the gates a little, just enough for you to slip out.\n");
	break;
    default:
	break;
    }
    return 0;
}

public void
reset_room()
{
    clone_npcs(Guard, MINAS_DIR + "npc/cguard", -1.0);

    if (objectp(Guard[0]))
    {
	Guard[0]->set_random_move(12);
	Guard[0]->set_restrain_path( ({ MINAS_DIR }) );
    }
}

public string
exa_gate()
{
    string  desc =
	"This is the Third Gate that guards the City. ";

    if (gate_closed())
	desc += "The gates are closed, and you will "
	     +  "not get through without a password.\n";
    else
	desc += "Presently, it is open.\n";

    return desc;
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


