/*
 * Basement in Cair Andros
 * /d/Gondor/anorien/cairandros/basement/ba27.c
 *
 * Varian - March, 2020
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
        "you can reach it by going through the opening in the south " +
        "wall.\n");
    add_item (({"east", "east wall", "eastern wall"}),
        "Much like the western wall, there are several beds lined " +
        "up against the stone blocks of the eastern wall. The beds " +
        "are really not much more than pallets, wooden boxes " +
        "filled with straw covered with a thick layer of linen.\n");
    add_item( ({"south", "southern wall", "south wall", "opening",
            "wide opening"}),
        "The southern wall has been left fairly plain, distinguished " +
        "only by single wide opening which leads into the hallway " +
        "beyond.\n");
    add_item( ({"north", "north wall", "northern wall"}),
        "A long wooden table has been pushed up against the " +
        "northern wall here.\n");
    add_item (({"west", "west wall", "western wall"}),
        "Much like the eastern wall, there are several beds lined " +
        "up against the stone blocks of the western wall. The beds " +
        "are really not much more than pallets, wooden boxes " +
        "filled with straw covered with a thick layer of linen.\n");
    add_item( ({"bunk", "bunks", "bed", "beds", "pallet", "pallets"}),
        "The beds in here have been lined up against both the " +
        "east and west walls. The beds themselves are sturdy " +
        "wooden boxes which have been filled with straw and then " +
        "covered with a thick linen blanket. They don't look " +
        "overly comfortable, but they would certainly be preferable " +
        "to sleeping on the stone floor.\n");

    set_no_exit_msg( ({"northwest", "northeast", "southwest",
            "southeast", "east", "north", "west"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");

    room_add_object(AN_OBJ_DIR + "table");

    add_npc(CA_NPC_DIR + "ca_officer");
    add_npc(CA_NPC_DIR + "ca_soldier", 1 + random(2));

    add_prop(ROOM_I_INSIDE,1);

    add_exit(CABASE_DIR + "wcor5", "south", 0, 0, 0);

    reset_room();
}

string
desc()
{
    write("You are currently inside some soldier's quarters in the " +
        "lower levels of Cair Andros. Plenty of simple bunks, really " +
        "nothing more than basic pallets, have been lined up against " +
        "both the east and west walls here. A long table has been " +
        "pushed up against the northern wall of the room here and " +
        "you can see the corridor you came in from through the wide " +
        "opening in the southern wall.\n");
}