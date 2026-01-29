/*
 * /d/Gondor/pelargir/rooms/belfalas11.c
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
    set_part(PART_SOUTH);
    set_street_name(STREET_BELFALAS);
    set_room_type(TYPE_STREET);

    set_extra_desc(
        STREET_BELFALAS + " has reached its southernmost stretch"
      + " here, as it winds to a halt before the city gates, which"
      + " lie just to the south. There is little to no traffic here,"
      + " as this entrance to the city is used far less than that"
      + " to the north.");

    add_item( ({ "gate", "gates", "city gate", "city gates",
                 "entrance" }), BSN(
        "The city gates are a short walk to the south, where a few"
      + " guards are visible patrolling the area."));
    add_item( ({ "guard", "guards" }), BSN(
        "The manner of the guards gives the impression that they"
      + " do not fear much action will take place on this end of"
      + " the city."));


    add_exit((PELAR_DIR + "streets/belfalas10"),    "northwest",0);
    add_exit((PELAR_DIR + "streets/s_gate_in"), "south",0);

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
