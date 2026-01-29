/*
 *  /d/Gondor/morgul/city/mmr4.c
 *
 *  This is about halfway up the length of the city on the main n-s strip.
 *
 *  Originally coded by Olorin (?) in 1993-1994
 *
 *  Revision History:
 *    Aug-20-1998 (Gorboth) General code revision
 *                          Added donation column as per Mercade's request
 */
#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

/*
 * Prototypes
 */
public void    create_morgul_room();
public void    reset_room();

/*
 * Function name: create_morgul_room
 * Description  : allows us to create the room with Morgul presets
 */
public void
create_morgul_room()
{
    FIX_EUID;	/* will be cloning a column */
    set_extraline("You are halfway up the road from the tower to the"
                + " Mordor Gate. To the north and south smaller streets"
                + " are branching off from the road.");
    set_road(2);
    set_side("south");
    add_mountain();
    add_item(({"gate","mordor gate"}), BSN(
        "In the distance to the east, you can see a great gate vaulted"
      + " beneath an archway in the city wall. This is the Mordor Gate,"
      + " the main gate of the city."));
    add_item(({"wall","walls","city wall","city walls"}), BSN(
        "The eastern city walls are visible from here. Where the " +
        "street meets the walls, you can make out a large gate."));

    add_exit(MORGUL_DIR + "city/darkstr3","north","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/mmr5","east","@@check_exit",2);
    add_exit(MORGUL_DIR + "city/darkstr2","south","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/mmr3","west","@@check_exit",1);

    reset_room();
} /* create_morgul_room */

/*
 * Function name: reset_room
 * Description  : we clone the donation column to the room here
 */
public void
reset_room()
{
    if (!objectp(present("column", TO)))
    {
	clone_object("/d/Genesis/obj/donation/column")->move(TO, 1);
    }
} /* reset_room */
