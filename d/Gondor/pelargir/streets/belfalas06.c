/*
 * /d/Gondor/pelargir/rooms/belfalas06.c
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
        STREET_ADMIRAL + " intersects with " + STREET_BELFALAS
      + " here, running east and west through the city."
      + " To the west, affluence appears to be the norm, as the"
      + " homes look quite lavish and well kept. The opposite"
      + " appears true of a few homes to the east.");

    add_item( ({ "homes to the west", "west", "western homes" }), BSN(
        "The homes to the west are in many cases spectacular"
      + " mansions, perhaps owned by landowners, or merchants"
      + " who have for many generations procured their fortunes"
      + " here in the city of Pelargir."));
    add_item( ({ "homes to the east", "east", "eastern homes" }), BSN(
        "Many of the homes to the east look fair enough, though"
      + " perhaps rather simple and small. Nestled there also,"
      + " however, what look to be a few places of ill-repute."));
    add_item( ({ "mansion", "mansions" }), BSN(
        "The mansions to the west are perhaps the largest in"
      + " the city of Pelargir."));
    add_item( ({ "homes of ill-repute",
                 "places of ill-repute" }), BSN(
        "A few of the homes to the east definitely have an"
      + " unsavory look to them."));


    add_exit((PELAR_DIR + "streets/belfalas05"), "north", 0);
    add_exit((PELAR_DIR + "streets/belfalas07"), "south", 0);
    add_exit((PELAR_DIR + "streets/admiral07"), "east", 0);
    add_exit((PELAR_DIR + "streets/admiral06"), "west", 0);

} /* create_pelargir_room */
