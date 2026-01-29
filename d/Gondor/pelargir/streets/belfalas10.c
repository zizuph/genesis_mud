
/*
 * /d/Gondor/pelargir/rooms/belfalas10.c
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

    set_extra_desc("To the north stands a bulky statue in the " +
        "city square of Pelargir. To the west is a smaller square " +
        "with an inn and the post office. The main street continues " +
        "southeast to the southern city gates, staying to the left " +
        "of a large stone building.");

    add_item( ({ "statue", "bulky statue" }),
        BSN("The statue is rather tall and bulky but " +
       "other than that you cannot see details without getting " +
       "closer."));
    add_item( ({ "post office", "inn" }),
        BSN("You would have to be closer to get a better look."));
    add_item( ({ "gates", "gate", "city gates", "southern city gates", }),
        BSN("The gates cannot be seen from here as the street makes a " +
        "turn between here and the gates."));
    add_item( ({ "building", "stone building", }),
        BSN("This large stone building is the Adventurers' Guild of " +
        "Pelargir. The building was constructed from grey stone blocks " +
        "hewn from rock and polished. Time and weather have left their " +
        "impact on the stones, but the expert workmanship is still " +
        "clearly visible. A large archway without doors is leading " +
        "into the building."));
    add_item( ({ "arch", "archway", "entrance", "doors", "door", }),
        BSN("A large archway is leading into the building of the " +
        "Adventurers' Guild. The arch itself was made from larger " +
        "stone slabs than the walls, fitted together to form half " +
        "a circle over the entrance. There are no doors blocking the " +
        "passage through the archway."));
    add_item( ({ "gate", "gates", "city gate", "city gates",
                 "southern city gates" }), BSN(
        "The southern city gates experience far less traffic than do"
      + " their counterparts to the north."));

    add_exit((PELAR_DIR + "streets/belfalas09"),   "north",0);
    add_exit((PELAR_DIR + "streets/belfalas11"),   "southeast",0);
    add_exit((PELAR_DIR + "misc/pelguild"),   "south",0);
    add_exit((PELAR_DIR + "streets/plaza"),    "west",0);
} /* create_pelargir_room */
