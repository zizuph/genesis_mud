/*
 * /d/Gondor/pelargir/rooms/shipwright03.c
 *
 *
 * Copyright (C) 1999 by Cooper Sherry (Gorboth) and
 *	Nancy L. Mintz (Gnadnar)
 * 
 */

#pragma strict_types

inherit "/d/Gondor/pelargir/pelargir_room";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/pelargir_room.h"


static object  Sailor;

public void	create_pelargir_room();
public void	reset_room();
public int	block_npc();


/*
 * Function name:	create_pelargir_room
 * Description	:	set up the room
 */
public void
create_pelargir_room()
{
    set_part(PART_EAST);
    set_street_name(STREET_SHIPWRIGHT);
    set_room_type(TYPE_STREET);

    set_extra_desc(
        "The docks of Pelargir run alongside the road to the east,"
      + " where ships and all the sights that accompany them are"
      + " visible. The street runs on to the north and south, and"
      + " just west of the road here, a well kept building looks"
      + " out over the port.");

    add_item( ({ "building", "well kept building",
                 "harbour master", }), BSN(
        "The building has been looked after with care, looking not"
      + " nearly so dirty and unpolished as the others along "
      + STREET_SHIPWRIGHT + ". A clever little window has been"
      + " fashioned to look like a porthole, and a large sign above"
      + " the door reads: 'The Harbour Master.'"));
    add_item( ({ "window", "porthole", "little window", "clever window",
                 "clever little window" }), BSN(
        "How clever! The window has been fashioned to look just like"
      + " the porthole of a ship."));
    add_item( ({ "door", "doorway" }), BSN(
        "The door looks sturdy and clean. It leads into the building"
      + " to the west."));
    add_item( ({ "sign", "large sign" }), BSN(
        "The sign reads: 'The Harbour Master.'"));

    add_cmd_item( ({ "sign", "large sign" }),
                  ({ "read" }), BSN(
        "The sign reads: 'The Harbour Master.'"));

    add_exit((PELAR_DIR + "streets/shipwright04"),    "north", 0);
    add_exit((PELAR_DIR + "docks/dock3"),     "east",  0);
    add_exit((PELAR_DIR + "streets/shipwright02"),    "south", 0);
    add_exit((PELAR_DIR + "docks/shipmastr"), "west",  block_npc);

    reset_room();
} /* create_pelargir_room */


/*
 * Function name:	reset_room
 * Description	:	create citizen
 */
public void
reset_room()
{
    Sailor = clone_npc(Sailor, SAILOR_FILE);
} /* reset_room */


/*
 * Function name:	block_npc
 * Description	:	don't let npcs into the harbour office
 * Returns	:	0 if exit allowed, 1 if blocked
 */
public int
block_npc()
{
    return TP->query_npc();
} /* block_npc */
