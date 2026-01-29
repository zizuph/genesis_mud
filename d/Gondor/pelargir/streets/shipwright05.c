/*
 * /d/Gondor/pelargir/rooms/shipwright05.c
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
    set_part(PART_EAST);
    set_street_name(STREET_SHIPWRIGHT);
    set_room_type(TYPE_STREET);

    set_extra_desc("To the north the Sirith river hurries past to join " +
        "the Anduin in its flow towards the sea. To the east it is " +
        "possible to step out on one of the docks where the ships " +
        "make port. South of here you may walk along " + 
        STREET_SHIPWRIGHT + ", which runs along all the docks.");

    add_item( ({ "sirith", "sirith river", "river sirith" }), BSN(
        "The Sirith River flows by a bit to the north, its waters"
      + " contained in a narrow channel."));
    add_item( ({ "channel", "narrow channel" }), BSN(
        "A narrow channel has been constructed to keep the waters of"
      + " the Sirith River in their course as they flow east through"
      + " Pelargir."));

    add_exit(PELAR_DIR + "docks/dock1","east",0);
    add_exit(PELAR_DIR + "streets/shipwright04","south",0);
    add_exit(PELAR_DIR + "docks/shipbldng","west",0);

} /* create_pelargir_room */
