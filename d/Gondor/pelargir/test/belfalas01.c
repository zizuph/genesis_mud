/*
 * /d/Gondor/pelargir/rooms/belfalas01.c
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
    set_part(PART_NORTH);
    set_street_name(STREET_BELFALAS);
    set_room_type(TYPE_STREET);

    set_extra_desc("The city gates rise to the north, and " +
        "beyond them lies the road to the Harlond. " +
    	"Beyond an intersection to the south, " + STREET_BELFALAS +
        " leads across a bridge spanning the Sirith River.");

    add_item( ({ "gates", "city gates", "northern city gates",
        "northern gates", "gate", "city gate",
        "northern city gate", "northern gate", }),
        BSN(STREET_BELFALAS + " leads north to the city gate, which " +
        "is flanked by thick towers. The city wall continues " +
        " east and west of the towers."));
    add_item( ({ "tower", "towers", "thick tower", "thick towers" }),
    BSN("The towers are the primary defense against invaders at the"
      + " gate. Archers are constantly on watch from their heights."));
    add_item( ({ "archer", "archers" }), BSN(
        "The archers do not face into the city, and therefore are not"
      + " visible from this vantage point."));
    add_item( ({ "wall", "city wall", "city walls" }), BSN(
        "The city walls travel away from the gate to the west"
      + " and east. Guards are visible partolling along the"
      + " battlements."));
    add_item( ({ "guard", "guards", "battlement", "battlements" }), BSN(
        "High atop the city walls, a few guards are visible patrolling"
      + " the battlements, peering always to the northeast."));
    add_item( ({ "road to the harlond", "harlond" }), BSN(
        "The Harlond lies far to the northeast, beyond the city"
      + " gates."));
    add_item( ({ "intersection", "south",
                 "intersection to the south" }), BSN(
        "A bit to the south, " + STREET_BELFALAS + " meets with "
      + STREET_BEACON + ", which travels to the east."));
    add_item( ({ "bridge", "sirith river", "river", "sirith",
                 "water", "river sirith", "waters" }), BSN(
        "The waters of the Sirith River flow beneath a bridge"
      + " to the south."));

    /* XXX update exit ... */
    add_exit((PELAR_DIR + "street/n_gate_in"), "north", 0);
    add_exit((PELAR_DIR + "test/belfalas02"), "south", 0);

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
