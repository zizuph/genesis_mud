/*
 *	/d/Gondor/minas/s1crc2.c
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

public int
antiques_closed()
{
    write("The door to the Antiques shop is closed and barred from inside.\n");
    return 1;
}

public void
create_street()
{
    set_circle("Second");
    set_areaname("southern");
    set_streetname("Lebennin Square");
    set_streettype("square");
    set_activity(2);
    set_wealth(1);
    add_exit(MINAS_DIR + "s2crc2",         "east",                0, 1);
    add_exit(MINAS_DIR + "rooms/antiques", "north", antiques_closed, 0);
    add_exit(MINAS_DIR + "alleycrc2",      "west",                0, 1);
    add_exit(MINAS_DIR + "rooms/armoury",  "south",               0, 0);

    set_extraline("To the south you see a small shop with a plaque above the door, "+
        "and a white building is to the north with a sign on the wall. ");
    add_item("shop","There are several shops here, among them an armoury to the "+
        "south, and an antique-shop to the north.\n");
    add_item("sign", "The sign reads: 'Milyamir's Antiques - Opening soon'\n");
    add_cmd_item("sign", "read",
		 "The sign reads: 'Milyamir's Antiques - Opening soon'\n");
    add_item("plaque", "The plaque reads:  Calmacil's Armours - Best in Gondor!\n");
    add_cmd_item("plaque", "read", 
		 "The plaque reads:  Calmacil's Armours - Best in Gondor!\n");

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

