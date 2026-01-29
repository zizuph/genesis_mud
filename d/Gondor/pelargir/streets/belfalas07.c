/*
 * /d/Gondor/pelargir/rooms/belfalas07.c
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

static object  Citizen;

public void	create_pelargir_room();
public void	reset_room();



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
        "To the east, a long and dusty building runs alongside the"
      + " street, its wooden walls resonating with the sounds of"
      + " animal activity. Numerous official looking buildings line"
      + " the street to the west.");


    add_item( ({ "long building", "dusty building", "east",
                 "long and dusty building",
                 "building to the east", "stable", "stables",
                 "stables of pelargir" }), BSN(
        "The building bears all the signs of typical stables, complete"
      + " with loud neighing from within."));
    add_item( ({ "walls", "wall", "wooden wall", "wooden walls", }), BSN(
        "There is a lot of noise coming from behind the stable walls."
      + " There must be quite a few horses in there, and some that"
      + " need feeding."));
    add_item( ({ "sounds", "animal activity", "animals", "animal",
                 "sound", "neigh", "neighing" }), BSN(
        "You can't see any of the actual beasts from here, but it"
      + " is quite obvious that more than just a few horses are within"
      + " the stables to the east."));
    add_item( ({ "official building", "official buildings",
                 "official looking building",
                 "official looking buildings",
                 "west" }), BSN(
        "The buildings to the west have the look of civic offices."));
    add_item( ({ "office", "offices", "civic office",
                 "civic offices" }), BSN(
        "It is unclear what function is performed in these buildings."));

    add_exit((PELAR_DIR + "streets/belfalas06"), "north", 0);
    add_exit((PELAR_DIR + "streets/belfalas08"), "south", 0);

    reset_room();
} /* create_pelargir_room */


/*
 * Function name:	reset_room
 * Description	:	create citizen
 */
public void
reset_room()
{
    Citizen = clone_npc(Citizen, CITIZEN_FILE);
} /* reset_room */
