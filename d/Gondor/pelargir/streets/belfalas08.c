/*
 * /d/Gondor/pelargir/rooms/belfalas08.c
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


public void	create_pelargir_room();


/*
 * Function name:	create_pelargir_room
 * Description	:	set up the room
 */
public void
create_pelargir_room()
{
    set_part(PART_WEST);
    set_street_name(STREET_BELFALAS);
    set_room_type(TYPE_STREET);

    set_extra_desc(
        "This part of town is known for its activity, and the crowded"
      + " streets bear testimony to this. Various carts and horse-drawn"
      + " carriages make their way up and down the street here, many"
      + " of them coming from just to the south, where Belfalas Square"
      + " is visible.");

    add_item( ({ "activity", "crowd", "crowds", "crowded street",
                 "crowded streets" }), BSN(
        "The activity along these streets continues day and night,"
      + " for in this City, there is always a ship at port, and a"
      + " delivery to be made."));
    add_item( ({ "cart", "carts" }), BSN(
        "While an occasional cart will pass by drawn by some beast"
      + " of burden or another, most are the hand driven variety,"
      + " pushed or pulled along by the busy owner."));
    add_item( ({ "carriage", "carriages", "horse-drawn carriage",
                 "horse-drawn carriages" }), BSN(
        "The streets clear some whenever one of the horse-drawn"
      + " carriages thunders past, drawing its occupats to parts"
      + " unknown."));
    add_item( ({ "south", "square", "belfalas square" }), BSN(
        "Just a ways to the south, the street can be seen opening"
      + " onto Belfalas Square, considered by many to symbolize the"
      + " main hub of activity in Pelargir."));

    add_exit((PELAR_DIR + "streets/belfalas07"), "north", 0);
    add_exit((PELAR_DIR + "streets/belfalas09"), "south", 0);

} /* create_pelargir_room */
