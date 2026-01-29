/*
 * Basement in Cair Andros
 * /d/Gondor/anorien/cairandros/basement/ba17.c
 *
 * Varian - February, 2020
 */

#pragma strict_types

#include "../../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit ANORIEN_STD_DIR + "bsmt_base";

/*
 * Function name:        create_bs_room()
 * Description  :        Creates a basement room in Cair Andros
 */

nomask void 
create_bs_room() 
{    
    set_items_barracks();

    set_short("Inside the lower barracks in Cair Andros");
    set_long("@@desc@@"); 

    add_item( ({"quarters", "barracks", "lower barracks", "here"}),
        "@@desc@@");
    add_item( ({"hall", "hallway"}),
        "This hallway leads through the lower levels of Cair Andros, " +
        "you can reach it by going through the opening in the west " +
        "wall.\n");
    add_item (({"north", "north wall", "northern wall"}),
        "Much like the southern wall, there are several beds lined " +
        "up against the stone blocks of the northern wall. The beds " +
        "are really not much more than pallets, wooden boxes " +
        "filled with straw covered with a thick layer of linen.\n");
    add_item( ({"west", "western wall", "west wall", "opening", 
            "wide opening"}),
        "The western wall has been left fairly plain, distinguished " +
        "only by single wide opening which leads into the hallway " +
        "beyond.\n");
    add_item( ({"east", "east wall", "eastern wall"}),
        "A wide stone monument stands in front of the eastern wall, " +
        "covered in names.\n");
    add_item( ({"south", "south wall", "southern wall"}),
        "Much like the northern wall, there are several beds lined " +
        "up against the stone blocks of the southern wall. The beds " +
        "are really not much more than pallets, wooden boxes " +
        "filled with straw covered with a thick layer of linen.\n");
    add_item( ({"bunk", "bunks", "bed", "beds", "pallet", "pallets"}),
        "The beds in here have been lined up against both the " +
        "north and south walls. The beds themselves are sturdy " +
        "wooden boxes which have been filled with straw and then " +
        "covered with a thick linen blanket. They don't look " +
        "overly comfortable, but they would certainly be preferable " +
        "to sleeping on the stone floor.\n");
    add_item( ({"monument", "wide monument", "wide stone monument",
            "stone monument", "cenotaph"}),
        "This is a wide stone monument that stretches out in front " +
        "of the eastern wall here. The date III 2901 is etched " +
        "at the top of the stone, and you estimate that a couple " +
        "thousand names have been carved below. It seems likely " +
        "that this is a cenotaph in honour of the men of Gondor " +
        "who fought, and died, defending this fortress when the " +
        "Uruk-Hai spilled out of Mordor and occupied Ithilien " +
        "over a hundred years ago.\n");

    set_no_exit_msg( ({"northwest", "northeast", "southwest",
            "southeast", "east", "north", "south"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");

    add_npc(CA_NPC_DIR + "ca_officer");
    add_npc(CA_NPC_DIR + "ca_soldier", 1 + random(2));

    add_prop(ROOM_I_INSIDE,1);

    add_exit(CABASE_DIR + "hall10", "west", 0, 0, 0);

    reset_room();
}

string
desc()
{
    write("This room in the lower levels of Cair Andros clearly serve " +
        "as sleeping quarters for many of the soldiers who have been " +
        "assigned the duty of defending this fortress. Dozens of bunks " +
        "are neatly lined up along the north and south walls, each " +
        "no more than a simple pallet, sufficient for the needs of a " +
        "common soldier. A stone monument stands firmly in front of " +
        "the eastern wall, and a wide opening in the western wall " +
        "will take you back out into the hallway you came from.\n");
}