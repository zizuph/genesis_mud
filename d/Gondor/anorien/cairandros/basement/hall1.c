/*
 * Basement in Cair Andros
 * /d/Gondor/anorien/cairandros/basement/hall1.c
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
    add_item( ({"south", "southern wall", "south wall"}),
        "The southern wall is almost entirely covered by the solid " +
        "looking stone staircase which leads to the upper levels " +
        "of Cair Andros.\n");
    add_item( ({"stair", "stairs", "staircase", "stairway",
            "stone stair", "stone stairs", "stone staircase",
            "stone stairway", "solid stair", "solid stairs",
            "solid staircase", "solid stairway", "wide stair",
            "wide stairs", "wide staircase", "wide stairway",
            "solid stone stair", "solid stone staircase",
            "solid stone stairs", "solid stone stairway",
            "wide stone stair", "wide stone staircase",
            "wide stone stairs", "wide stone stairway"}),
        "This wide stone staircase looks is made from large blocks " +
        "of a dark grey granite. It looks like the staircase is " +
        "wide enough to accomodate five or six men at a time as " +
        "it leads towards the upper levels of Cair Andros.\n");
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
        "There are three walls here, did you want to examine one " +
        "of them in particular?\n");

    set_no_exit_msg( ({"northwest", "northeast", "southwest",
            "southeast"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");
    set_no_exit_msg( ("south"),
        "You cannot go south, the stairs are in the way. You could " +
        "go up instead.\n");

    add_npc(CA_NPC_DIR + "ca_soldier", -1 + random(3));

    add_prop(ROOM_I_INSIDE,1);

    add_exit(CABASE_DIR + "ba1", "east", 0, 0, 0);
    add_exit(CABASE_DIR + "ba2", "west", 0, 0, 0);
    add_exit(CABASE_DIR + "hall2", "north", 0, 0, 0);
    add_exit(CAIRANDROS_DIR + "fort3", "up", 0, 0, 0);

    reset_room();
}

string
desc()
{
    write("You are standing at the base of a stone staircase in the " +
        "lower levels of Cair Andros. This solid staircase, carved " +
        "from grey stone, marches up the southern wall, leading up " +
        "into the rest of the fortress above. A hallway stretches " +
        "out ahead of you to the north, while openings in both the " +
        "east and west walls lead into rooms where the soldiers " +
        "of the fortress sleep. Several torches line the walls " +
        "of the hallway, giving plenty of light from their " +
        "flickering flames.\n");
}