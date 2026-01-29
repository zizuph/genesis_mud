/*
 * /d/Gondor/minas/gate1.c
 *
 * Just within the first circle of Minas Tirith at the west side of the
 * Great Gate.
 *
 * Originally coded by Elessar (?) 1992-1993
 *
 * Revision History:
 *   Aug-20-1998 (Gorboth) : general code revision
 *                           added donation column as per Mercades request
 *  Last modified by Alto, 09 June 2001
 *      Added room tells and revised descriptions
 */
#pragma strict_types

inherit "/d/Gondor/minas/lib/street.c";
inherit "/d/Gondor/minas/lib/street_funcs.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

/*
 * Prototypes
 */
public void    create_street();
public void    reset_room();
public int     checkgate();
public string  gate_desc();

/*
 * Global Variables
 */
static object  Guard1,
               Guard2;

/*
 * Function name: create_street
 * Description  : allows us to create the room with area presets
 */
public void
create_street() 
{
    FIX_EUID; /* will be cloning guards, column */
    set_streetlight(2);
    set_streetname("Main Street");
    set_streettype("broad street");
    set_areaname("eastern");
    set_circle("First");
    set_activity(2);
    set_wealth(1);
    set_extraline("To the east you see the great First Gate of Minas"
                + " Tirith, which leads through the First Wall and out"
                + " into the fields of Pelennor. Several guards stand"
                + " by the gate, checking the people who want to enter"
                + " the city. Upon the wall you see more guards.");
    add_item("gate", gate_desc);
    add_item( ({"guards"}), BSN(
        "The guards have quite an important job here, preventing spies"
      + " from the Evil One from entering the city of Minas Tirith."));
    add_item( ({"wall"}), BSN(
        "The First Wall is the outer wall of the City, and therefore has"
      + " been build to be the strontest. Upon the top of the battlements"
      + " guards can be seen walking around, watching the fields outside"
      + " the wall."));
    add_exit(MINAS_DIR + "e3crc1",  "north", 0, 1);
    add_exit(MINAS_DIR + "ingate1", "east",  0, 1);
    add_exit(MINAS_DIR + "e2crc1",  "south", 0, 1);

    /* These items are similar in all streets on all levels */

    add_street_items();

    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    reset_room();
} /* create_street */

/*
 * Function name: reset_room
 * Description  : clone the npcs and column into the room
 */
public void
reset_room()
{
    Guard1 = clone_npc(Guard1, MINAS_DIR + "npc/cguard");
    Guard2 = clone_npc(Guard2, MINAS_DIR + "npc/cguard");
    if (!objectp(present("column", TO)))
    {
	clone_object("/d/Genesis/obj/donation/column")->move(TO, 1);
    }
} /* reset_room */

/*
 * Function name: checkgate
 * Description  : gives a time-based message as one passes the gate
 * Returns      : 0 - TP = player (to whom we give the message)
 *                1 - TP = npc (for whom we dont waste cpu)
 */
public int
checkgate()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();

    if (TP->query_npc()) 
        return 1;

    switch (time)
    {
    case "night":
        write("The guards open a small hatch in the gate, peeking "
            + "out to see if it is safe to open.\n"
            + "Then they open the gate just enough to let you out.\n");
        return 0;
        break;
    default:
        WRITE("You walk out through the Gate, greeting the guards as you"
            + " pass them.");
        return 0;
    }
} /* checkgate */

/*
 * Function name: gate_desc
 * Description  : provides a description of the gate, based on their
 *                open/closed status (closed at night)
 * Returns      : desc for the gate (string)
 */
public string
gate_desc()
{
    string  time  = tod(),
            desc  = "The First Gate is the strongest of the seven "
        + "gates in Minas Tirith, so the people can live quite safely "
        + "inside its great wooden doors.";

    switch (time)
    {
    case "night":
        desc += " Since it is night, the gates are closed.";
        break;
    default:
        desc += " For now the gates are open.";
    }
    return BSN(desc);
} /* gate_desc */


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
