/*
 * /d/Gondor/pelargir/rooms/shipwright02.c
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


static object  Thief;

public void	create_pelargir_room();
public void	reset_room();


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
        "To the west, a number of workers are busy in a stockyard which"
      + " contains a good deal of cargo waiting to be loaded at port."
      + " The street continues on to the north and south, where fresh"
      + " air rolls in from the river to the east, where the docks are"
      + " filled with ships.");

    add_item( ({ "workers", "number of workers", "worker" }), BSN(
        "The workers are busy stacking crates which are perhaps waiting"
      + " to be onloaded when their ship comes to port."));
    add_item( ({ "create", "crates" }), BSN(
        "There are hundreds of crates in the stockyard. Some workers"
      + " are visible toiling over them."));
    add_item( ({ "stockyard", "yard", "west" }), BSN(
        "The stockyard to the west is fenced off from the street, and"
      + " looks rather dark and dirty. Some workers are visible"
      + " within, moving some crates into storage."));
    add_item( ({ "fence", "stockyard fence" }), BSN(
        "The stockyard fence is made of iron which has been painted"
      + " black, and runs along the road to the west."));
    add_item( ({ "cargo" }), BSN(
        "The cargo in the stockyard is packed within hundreds of"
      + " crates. There is no telling what it could be."));
    add_item( ({ "air", "fresh air" }), BSN(
        "The air which rolls into town from the River Anduin is very"
      + " fresh indeed."));

    add_exit((PELAR_DIR + "test/shipwright03"), "north", 0);
    add_exit((PELAR_DIR + "docks/dock4"), "east", 0);
    add_exit((PELAR_DIR + "test/shipwright01"), "south", 0);

    reset_room();
} /* create_pelargir_room */


/*
 * Function name:	reset_room
 * Description	:	create citizen
 */
public void
reset_room()
{
    Thief = clone_npc(Thief, THIEF_FILE);
} /* reset_room */
