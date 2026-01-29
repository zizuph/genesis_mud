/*
 * /d/Gondor/pelargir/rooms/market01.c
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
    set_street_name(STREET_MARKET);
    set_room_type(TYPE_STREET);

    set_extra_desc(
        STREET_MARKET + " grows quickly crowded to the west, where"
      + " it enters Belfalas Square which bustles with activity."
      + " Eastward, the surroundings immediately turn to things"
      + " associated with the docks, which are visible in the"
      + " distance at the end of the street in that direction."
      + " A squat building to the north opens directly on to the"
      + " street here, proudly bearing a sign pained in bold"
      + " black letters.");

    add_item( ({ "square", "belfalas square", "west", "activity" }), BSN(
        "To the west, Belfalas Square is visible through a thick"
      + " crowd of people, all seemingly on their way somewhere with"
      + " somthing. "));
    add_item( ({ "crowd", "thick crowd", "crowd of people",
                 "people", "thick crowd of people" }), BSN(
        "There is all sorts of activity in this part of town. Some"
      + " people are carting fish around, others crates of shellfish,"
      + " others yet, exotic goods brought in from other ports."));
    add_item( ({ "building", "squat building", "north",
                 "squat building to the north", "mason shop",
                 "masonry shop" }), BSN(
        "The building looks to have been built by able hands that"
      + " care more for structural integrity and efficiency than"
      + " beauty in design. It looks like it could withstand a tidal"
      + " wave. A sign has been painted in bold black letters on"
      + " the building."));
    add_item( ({ "sign", "letters", "bold letters", "black letters",
                 "bold black letters" }), BSN(
        "The sign is pained with thick black letters that read:"
      + " 'MASON'"));

    add_cmd_item( ({ "sign", "letters", "bold letters", "black letters",
                     "bold black letters" }),
                  ({ "read" }), BSN(
        "The sign reads: 'MASON'"));


    add_exit((PELAR_DIR + "test/market02"), "east", 0);
    add_exit((PELAR_DIR + "test/belfalas09"), "west", 0);
    add_exit((PELAR_DIR + "misc/pelstone"), "north", 0);

} /* create_pelargir_room */
