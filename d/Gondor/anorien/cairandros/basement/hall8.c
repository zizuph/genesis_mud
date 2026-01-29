/*
 * Basement in Cair Andros
 * /d/Gondor/anorien/cairandros/basement/hall8.c
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

    set_short("Hallway in the lower levels of Cair Andros");
    set_long("@@desc@@"); 

    add_item( ({"hall", "hallway", "here"}),
        "@@desc@@");
    add_item( ({"room", "barracks", "rooms", "quarters",
            "sleeping quarters"}),
        "You can see two large rooms through the wide openings in " +
        "the east and west walls. It looks like these rooms are " +
        "primarily being used as sleeping quarters.\n");
    add_item (({"north", "northern hall", "north hall"}),
        "The hallway continues to stretch out before you to the " +
        "north, with wide openings in both the east and west walls " +
        "every so often.\n");
    add_item( ({"east", "eastern wall", "east wall"}),
        "The eastern wall of the hallways is made from the same " +
        "grey stone as the rest of the fortress, broken up only " +
        "by the occasional torch and several wide openings that " +
        "lead into rooms.\n");
    add_item( ({"west", "western wall", "west wall"}),
        "The western wall of the hallways is made from the same " +
        "grey stone as the rest of the fortress, broken up only " +
        "by the occasional torch and several wide openings that " +
        "lead into rooms.\n");
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
        "end of this hallway.\n");
    add_item( ({"east opening", "eastern opening"}),
        "This opening in the east wall leads into a room used " +
        "as sleeping quarters for the soldiers here.\n");
    add_item( ({"west opening", "western opening"}),
        "This opening in the west wall leads into a room used " +
        "as sleeping quarters for the soldiers here\n");
    add_item( ({"opening", "openings"}),
        "There are two openings here, in both the eastern and " +
        "western walls.\n");
    add_item( ({"wall", "walls"}),
        "There are two walls here, did you want to examine one " +
        "of them in particular?\n");

    set_no_exit_msg( ({"northwest", "northeast", "southwest",
            "southeast"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");

    add_npc(CA_NPC_DIR + "ca_soldier", -1 + random(3));

    add_prop(ROOM_I_INSIDE,1);

    add_exit(CABASE_DIR + "ba13", "east", 0, 0, 0);
    add_exit(CABASE_DIR + "ba14", "west", 0, 0, 0);
    add_exit(CABASE_DIR + "hall9", "north", 0, 0, 0);
    add_exit(CABASE_DIR + "hall7", "south", 0, 0, 0);

    reset_room();
}

string
desc()
{
    write("You are currently in the lower levels of the fortress " +
        "on the island of Cair Andros in Gondor. A hallway stretches " +
        "away from you to both the north and south, while openings " +
        "in the east and west walls lead into rooms where the soldiers " +
        "soldiers serving here sleep. Several torches line the walls " +
        "of the hallway, giving plenty of light from their " +
        "flickering flames.\n");
}