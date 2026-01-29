/*
 * Basement in Cair Andros
 * /d/Gondor/anorien/cairandros/basement/ecor5.c
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

    set_short("Corridor in the lower levels of Cair Andros");
    set_long("@@desc@@"); 

    add_item( ({"corridor", "here"}),
        "@@desc@@");
    add_item( ({"room", "barracks", "rooms", "quarters",
            "sleeping quarters"}),
        "You can see two large rooms through the wide openings in " +
        "the north and south walls. It looks like these rooms are " +
        "primarily being used as sleeping quarters.\n");
    add_item (({"north", "northern wall", "north wall"}),
        "The northern wall of the corridor is made from the same " +
        "grey stone as the rest of the fortress, broken up only " +
        "by the occasional torch and several wide openings that " +
        "lead into rooms.\n");
    add_item( ({"east", "eastern wall", "east wall"}),
        "The hallway ends here, and the way east is blocked " +
        "by a plain wall of grey stone.\n");
    add_item( ({"west", "western corridor", "west corridor"}),
        "The corridor continues to stretch out before you to the " +
        "west, with wide openings in both the north and south walls " +
        "every so often.\n");
    add_item( ({"south", "southern wall", "south wall"}),
        "The southern wall of the corridor is made from the same " +
        "grey stone as the rest of the fortress, broken up only " +
        "by the occasional torch and several wide openings that " +
        "lead into rooms.\n");
    add_item( ({"stair", "stairs", "staircase", "stairway",
            "stone stair", "stone stairs", "stone staircase",
            "stone stairway", "solid stair", "solid stairs",
            "solid staircase", "solid stairway", "wide stair",
            "wide stairs", "wide staircase", "wide stairway",
            "solid stone stair", "solid stone staircase",
            "solid stone stairs", "solid stone stairway",
            "wide stone stair", "wide stone staircase",
            "wide stone stairs", "wide stone stairway"}),
        "There is a wide stone staircase somewhere at the southern " +
        "end of the north-south hallway.\n");
    add_item( ({"north opening", "northern opening"}),
        "This opening in the north wall leads into a room used " +
        "as sleeping quarters for the soldiers here.\n");
    add_item( ({"south opening", "southern opening"}),
        "This opening in the south wall leads into a room used " +
        "as sleeping quarters for the soldiers here\n");
    add_item( ({"opening", "openings"}),
        "There are two openings here, in both the northern and " +
        "southern walls.\n");
    add_item( ({"wall", "walls"}),
        "There are three walls here, did you want to examine one " +
        "of them in particular?\n");

    set_no_exit_msg( ({"northwest", "northeast", "southwest",
            "southeast"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");

    add_npc(CA_NPC_DIR + "ca_soldier", -1 + random(3));

    add_prop(ROOM_I_INSIDE,1);

    add_exit(CABASE_DIR + "ecor4", "west", 0, 0, 0);
    add_exit(CABASE_DIR + "ba37", "north", 0, 0, 0);
    add_exit(CABASE_DIR + "ba38", "south", 0, 0, 0);

    reset_room();
}

string
desc()
{
    write("You are currently in the lower levels of the fortress " +
        "on the island of Cair Andros in Gondor. The long corridor " +
        "you are in ends in a stone wall to the east and runs west " +
        "toward an intersection in the distance. There are openings " +
        "in the north and south walls, leading into rooms where the " +
        "soldiers serving here sleep. Several torches line the walls " +
        "of the hallway, giving plenty of light from their " +
        "flickering flames.\n");
}