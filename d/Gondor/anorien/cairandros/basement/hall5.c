/*
 * Basement in Cair Andros
 * /d/Gondor/anorien/cairandros/basement/hall5.c
 *
 * Varian - March, 2020
 */

#pragma strict_types

#include "../../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit ANORIEN_STD_DIR + "bsmt_base";

/*
 * Function name:        create_anorien_room()
 * Description  :        Creates a room in Anorien
 */

nomask void 
create_bs_room() 
{    
    set_items_hall();

    set_short("Intersection in the lower levels of Cair Andros");
    set_long("@@desc@@"); 

    add_item( ({"intersection", "here"}),
        "@@desc@@");
    add_item( ({"room", "barracks", "rooms", "quarters",
            "sleeping quarters"}),
        "There are plenty of rooms quartering the soldiers down " +
        "here, but you cannot enter any of them from the intersection " +
        "here.\n");
    add_item (({"north", "northern hall", "north hall"}),
        "The hallway continues to stretch out before you to the " +
        "north, with wide openings in both the east and west walls " +
        "every so often.\n");
    add_item( ({"east", "eastern corridor", "east corridor"}),
        "The corridor continues to stretch out before you to the " +
        "east, with wide openings in both the north and south walls " +
        "every so often.\n");
    add_item( ({"west", "western corridor", "west corridor"}),
        "The corridor continues to stretch out before you to the " +
        "west, with wide openings in both the north and south walls " +
        "every so often.\n");
    add_item( ({"south", "southern hall", "south hall"}),
        "The hallway continues to stretch out before you to the " +
        "south, with wide openings in both the east and west walls " +
        "every so often.\n");
    add_item( ({"stair", "stairs", "staircase", "stairway",
            "stone stair", "stone stairs", "stone staircase",
            "stone stairway", "solid stair", "solid stairs",
            "solid staircase", "solid stairway", "wide stair",
            "wide stairs", "wide staircase", "wide stairway",
            "solid stone stair", "solid stone staircase",
            "solid stone stairs", "solid stone stairway",
            "wide stone stair", "wide stone staircase",
            "wide stone stairs", "wide stone stairway"}),
        "There is a wide stone staircase at the very southern " +
        "end of the hallway.\n");
    add_item( ({"opening", "openings"}),
        "There are plenty of openings down the hallways and " +
        "corridors leading away from this intersection.\n");
    add_item( ({"wall", "walls"}),
        "There are no walls here! You are in the middle of an " +
        "intersection, where an east-west corridor meets the " +
        "primary hallway that runs north-south.\n");
    add_item( ({"corner", "corners"}),
        "As you would expect at an intersection like this one, " +
        "there are four corners here. They really are not very " +
        "exciting to look at.\n");

    set_no_exit_msg( ({"northwest", "northeast", "southwest",
            "southeast"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");

    add_npc(CA_NPC_DIR + "ca_soldier", -1 + random(3));

    add_prop(ROOM_I_INSIDE,1);

    add_exit(CABASE_DIR + "ecor1", "east", 0, 0, 0);
    add_exit(CABASE_DIR + "wcor1", "west", 0, 0, 0);
    add_exit(CABASE_DIR + "hall6", "north", 0, 0, 0);
    add_exit(CABASE_DIR + "hall4", "south", 0, 0, 0);

    reset_room();
}

string
desc()
{
    write("You are in the middle of an intersection, where a wide " +
        "hallway running north and south meets up with a long " +
        "corridor that stretches out to the east and the west. " +
        "There are plenty of wide openings visible in the light " +
        "of the torches down both the hallway and the corridor. " +
        "The staircase which leads back to the upper levels of " +
        "the fortress is at the very southern end of the hallway.\n");
}