/*
 *	/d/Gondor/minas/e2crc1.c
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

public int     check_open();
public void    reset_room();

static object  Guard;

public void
create_street() 
{
    set_streetname("Main Street");
    set_circle("First");
    set_streettype("street");
    set_areaname("eastern");
    set_streetlight(2);
    set_activity(1);
    set_wealth(2);
    add_exit(MINAS_DIR + "gate1",         "north", 0, 1);
    add_exit(MINAS_DIR + "wall/sinwall1", "east",  0, 0);
    add_exit(MINAS_DIR + "e1crc1",        "south", 0, 1);
    add_exit(MINAS_DIR + "rooms/mtpost",  "west",  check_open, 0);
    set_extraline("The Main Street runs north and south here, and to the " +
		  "north you can see the Main Gate. To the west is the " +
		  "post-office of Minas Tirith.");
    add_item("gate", "It is further north from here.\n");
    /* These items are similar in all streets on all levels */

    add_street_items();

    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    reset_room();
}
 
public int
check_open() 
{
    if (TP->query_npc()) 
	return 1;
    return 0;
}
 
public void
reset_room()
{
    Guard = clone_npc(Guard, MINAS_DIR + "npc/cguard");
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

