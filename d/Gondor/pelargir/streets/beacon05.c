/*
 * /d/Gondor/pelargir/rooms/beacon05.c
 *
 *
 * Copyright (C) 1999 by Cooper Sherry (Gorboth) and
 *	Nancy L. Mintz (Gnadnar)
 * 
 */

#pragma strict_types

inherit "/d/Gondor/pelargir/pelargir_room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/pelargir_room.h"


#define MIN_STR		15
#define SEWER_ROOM	(PELAR_DIR + "sewers/grate")


public void	create_pelargir_room();
public void	reset_room();
public void	init();
public string	exa_grating();
public int	open_grating(string str);


/*
 * Function name:	create_pelargir_room
 * Description	:	set up the room
 */
public void
create_pelargir_room()
{
    set_part(PART_NORTH);
    set_street_name(STREET_BEACON);
    set_room_type(TYPE_STREET);

    set_extra_desc(
        "The road traverses the expanse of a peninsula here, which"
      + " narrows as it juts out into the River Anduin to the east."
      + " The lighthouse of Pelargir rises majestically on the"
      + " crown of the peninsula, where " + STREET_BEACON + " comes"
      + " to an end before its base. On the road, there is a metal"
      + " grating set within the ground.");

    add_item( ({ "road", "street", "ground" }), BSN(
        "To the east, " + STREET_BEACON + " comes to an end before the"
      + " base of a tall lighthouse. Directly underfoot, a metal"
      + " grating has been set in the ground."));
    add_item( ({ "lighthouse", "lighthouse of pelargir" }), BSN(
        "The lighthouse of Pelargir stands atop the crown of the"
      + " peninsula to the east, set as a beacon for wayward"
      + " ships searching for safety amongst the troubled waters."
      + " It looks ancient and strong."));
    add_item( ({ "river", "river anduin", "anduin river", "anduin",
                 "anduin the great", "water", "waters", "mighty river",
                 "mighty anduin" }), BSN(
        "The mighty Anduin river flows majestically to the east,"
      + " where its waters flow around the feet of a peninsula which"
      + " juts out into its vast expanse. The Sirith River is visible"
      + " to the south, emptying its contents into the greater river"
      + " from the narrow channel which guided it through the city to"
      + " the west."));
    add_item( ({ "hole", "opening", "grate", "grating", "metal grating" }),
        exa_grating);
    add_item( ({ "peninsula" }), BSN(
        "The peninsula expands outward from the mainland into the"
      + " deep waters of the River Anduin to the east. Below and"
      + " to the south, the currents of the river are stifled by"
      + " the peninsula, allowing the docks of Pelargir to enjoy"
      + " nearly perfect conditions."));
    add_item( ({ "crown", "crown of the peninsula" }), BSN(
        "Upon the crown of the peninsula to the east, a tall"
      + " lighthouse rises from the ground."));
    add_item( ({ "base", "base of the lighthouse" }), BSN(
        "A door is set within the base of the lighthouse."));
    add_item( ({ "door", "lighthouse door" }), BSN(
        "From this distance, the door looks quite tiny against the"
      + " massive structure of the lighthouse."));
    add_item( ({ "mainland", "west" }), BSN(
        "To the west, the city stretches into the distance."));
    add_item( ({ "docks", "dock", "docks of pelargir" }), BSN(
        "The docks are far below and to the south from atop this"
      + " peninsula. The masts of the ships look tiny from these"
      + " heights."));
    add_item( ({ "sirith", "river sirith", "sirith river" }), BSN(
        "South of the peninsula, the Sirith River joins with the"
      + " mighty Anduin."));

    add_exit((PELAR_DIR + "streets/beacon04"), "west", 0);
    add_exit((PELAR_DIR + "streets/beacon06"), "east", 0);

    FIX_EUID
    SEWER_ROOM->load_me();
    SEWER_ROOM->reset_grating();
    reset_room();

} /* create_pelargir_room */


/*
 * Function name:	reset_room
 * Description	:	close grating
 */
public void
reset_room()
{
    SEWER_ROOM->reset_grating();
    remove_exit("down");
} /* reset_room */


/*
 * Function name:	init
 * Description	:	add verbs for grating
 */
public void
init()
{
    ::init();

    add_action(open_grating, "break");
    add_action(open_grating, "open");
    add_action(open_grating, "pull");
} /* init */


/* 
 * Function name:	exa_grating
 * Description	:	VBFC for the grating
 * Returns	:	string -- the description
 */
public string
exa_grating()
{
    int     open;
    string  ld = "The opening probably leads down into the sewers, " +
                 "taking up the rain water to prevent a flooding of the " +
                 "street.";

    open = SEWER_ROOM->query_open();

    if (open)
    {
        ld += " The metal grating covering the hole is rusty and broken, " +
              "so it cannot stop anyone from entering the sewers anymore.";
    }
    else
    {
        ld += " An old rusty metal grating is covering the hole, preventing " +
              "people from falling down into the sewers.";
    }
    
    return BSN(ld);
} /* exa_grating */


/*
 * Function name:	open_grating
 * Description	:	respond to attempts to open the grating
 * Arguments	:	string str -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
open_grating(string str)
{
    int     open;
    string  vb = QVB;

    if (str != "grate" &&
        str != "grating" &&
        str != "metal grating")
    {
        NF0(CAP(vb) + " what?\n");
    }

    SEWER_ROOM->load_me();
    open = SEWER_ROOM->query_open();

    if (open)
    {
        NFN0("The grating is broken and does not block the entrance into the " +
             "sewers anymore.");
    }

    if (TP->query_stat(SS_STR) < MIN_STR)
    {
        write("You try to " + vb + " the rusty grating, but you are too weak.\n");
        say(QCTNAME(TP) + " tries to " + vb + " the rusty grating, but fails.\n");
        return 1;
    }
    write("You pull at the rusty grating, and without much effort you manage " +
        "to break it.\n" +
        "The way leading into the sewers is open now.\n");
    say(QCTNAME(TP)+" pulls at the rusty grating and breaks it.\n" +
        "The way leading into the sewers is open now.\n");

    add_exit((PELAR_DIR + "sewers/grate"), "down", 0, 2);
    SEWER_ROOM->set_open();
    return 1;
} /* open_grating */
