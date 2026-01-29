/*
 *	/d/Gondor/minas/gate2.c
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

static object *Guard = allocate(3);

public void
create_street() 
{
    set_circle("Second");
    set_areaname("south-eastern");
    set_streetname("Main Street");
    set_streettype("broad street");
    set_activity(2);
    set_wealth(1);

    add_exit(MINAS_DIR + "e1crc2", "northeast", 0, 1);
    add_exit(MINAS_DIR + "s1crc1", "southeast", 0, 1);
    add_exit(MINAS_DIR + "s2crc2", "southwest", 0, 1);

    set_extraline("To the southeast lies the Second Gate of Minas " +
	"Tirith, which leads out to the First Circle. Guards " +
        "stand by the gate, watching the people who pass through " +
        "it. Upon the wall are more guards. The street here " +
        "continues northeast and southwest, following the Second " +
        "Circle.");
    add_item("guards", BSN("The guards, clad in black and silver " +
	"armour are here to guard the gate from trespassers and " +
	"people who are not allowed to pass further into the city."));
    add_item("gate", "The great Second Gate is just southeast from " +
	"here and leads out to the First Circle of the city.\n");
    /* These items are similar in all streets on all levels */

    add_street_items();

    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    reset_room();
}

public void
reset_room()
{
    clone_npcs(Guard, MINAS_DIR + "npc/cguard", -1.0);

    if (objectp(Guard[0]))
    {
	Guard[0]->set_random_move(20);
	Guard[0]->set_restrain_path( ({ MINAS_DIR }) );
    }
    if (objectp(Guard[1]))
    {
	Guard[1]->set_random_move(10);
	Guard[1]->set_restrain_path( ({ MINAS_DIR }) );
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
