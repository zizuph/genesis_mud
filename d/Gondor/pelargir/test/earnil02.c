/*
 * /d/Gondor/pelargir/rooms/earnil02.c
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
    set_part(PART_SOUTH);
    set_street_name(STREET_EARNIL);
    set_room_type(TYPE_STREET);

    set_extra_desc("To the north is a small orphanage. " +
        "There is an unfavorable scent " +
        "in the air, which may come from the refuse in the street, or " +
        "from the shack to the south. Though there are many homes " +
        "around here, it does not seem that any of them are too " +
        "receptive to visitors.");

    add_item("orphanage",
        BSN("The orphanage looks rather gloomy and " +
        "boring. It surely cannot be an interesting place to live."));
    add_item("refuse",
        BSN("The refuse here in the street seems to " +
        "attract a lot of attention.... from the flies at least."));
    add_item("shack",
        BSN("The shack looks like a strong wind is all " +
        "it would take to blow it right over. It would seem to be safer " +
        "just to live in the street."));

    add_exit((PELAR_DIR + "homes/orphanage"),  "north", 0);
    add_exit((PELAR_DIR + "test/earnil03"),    "east", 0);
    add_exit((PELAR_DIR + "homes/shack1"),     "south", 0);
    add_exit((PELAR_DIR + "test/earnil01"),     "west", 0);

} /* create_pelargir_room */
