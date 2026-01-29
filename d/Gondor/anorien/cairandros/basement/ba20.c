/*
 * Basement in Cair Andros
 * /d/Gondor/anorien/cairandros/basement/ba1.c
 *
 * Varian - February, 2020
 */

#pragma strict_types
#include "../../defs.h"

inherit ANORIEN_STD_DIR + "bsmt_base";
#include <stdproperties.h>
#include <macros.h>

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
        "you can reach it by going through the opening in the north " +
        "wall.\n");
    add_item (({"west", "west wall", "western wall"}),
        "Much like the eastern wall, there are several beds lined " +
        "up against the stone blocks of the western wall. The beds " +
        "are really not much more than pallets, wooden boxes " +
        "filled with straw covered with a thick layer of linen.\n");
    add_item( ({"north", "northern wall", "north wall", "opening",
            "wide opening"}),
        "The northern wall has been left fairly plain, distinguished " +
        "only by single wide opening which leads into the hallway " +
        "beyond.\n");
    add_item( ({"south", "southern wall", "space", "open space",
            "south wall"}),
        "An open platform, built of wood, has been placed near the " +
        "southern wall. Stacked on top of the platform are dozens " +
        "of large sacks.\n");
    add_item (({"east", "east wall", "eastern wall"}),
        "Much like the western wall, there are several beds lined " +
        "up against the stone blocks of the eastern wall. The beds " +
        "are really not much more than pallets, wooden boxes " +
        "filled with straw covered with a thick layer of linen.\n");
    add_item( ({"bunk", "bunks", "bed", "beds", "pallet", "pallets"}),
        "The beds in here have been lined up against both the " +
        "east and west walls. The beds themselves are sturdy " +
        "wooden boxes which have been filled with straw and then " +
        "covered with a thick linen blanket. They don't look " +
        "overly comfortable, but they would certainly be preferable " +
        "to sleeping on the stone floor.\n");
    add_item( ({"platform", "open platform", "wooden platform",
            "open wooden platform"}),
        "This platform is quite large, stretching across most of " +
        "the southern wall. The platform consists of long wooden " +
        "planks lifted up off the floor by being stretched " +
        "across wide beams of wood.\n");
    add_item( ({"long planks", "wooden planks", "wooden plank",
            "long plank", "long wooden plank", "long wooden planks",
            "plank", "planks"}),
        "These long planks of wood are raised up off the stone " +
        "floor, resting across some wooden beams to make a " +
        "platform.\n");
    add_item( ({"wide beams", "wooden beams", "wooden beam",
            "wide beam", "wide wooden beam", "beams",
            "beam", "wide wooden beams"}),
        "A few wide beams of wood stretch across the floor " +
        "near the southern wall of the room, providing a " +
        "base for some long planks of wood to rest on, forming " +
        "an open platform.\n");
    add_item( ({"large flour sacks", "large flour sack", "sacks",
            "flour sack", "flour sacks", "large sack", "sack",
            "large sacks", "flour"}),
        "Dozens of large sacks have been stacked on top of the " +
        "wooden platform here. Upon closer inspection, it seems " +
        "like these sacks are filled with supplies of flour.\n");

    set_no_exit_msg( ({"northwest", "northeast", "southwest",
            "southeast", "east", "west", "south"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");

    add_npc(CA_NPC_DIR + "ca_officer");
    add_npc(CA_NPC_DIR + "ca_soldier", 1 + random(2));

    add_prop(ROOM_I_INSIDE,1);

    add_exit(CABASE_DIR + "wcor1", "north", 0, 0, 0);

    reset_room();
}

string
desc()
{
    write("You are in the sleeping quarters designated for some " +
        "of the soldiers who are stationed in the fortress of " +
        "Cair Andros. The lower levels of the fort seem to be " +
        "filled with rooms just like this one, with plenty of " +
        "small pallets for beds lined up against the east and " +
        "west walls. An open space has been cleared against the " +
        "southern wall, where dozens of large sacks have been " +
        "stacked on top of an open wooden platform. You can see " +
        "the corridor you came in from through a wide opening " +
        "in the northern wall.\n");
}