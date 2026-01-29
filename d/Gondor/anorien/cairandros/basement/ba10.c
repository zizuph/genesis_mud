/*
 * Basement in Cair Andros
 * /d/Gondor/anorien/cairandros/basement/ba10.c
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
    add_item( ({"east", "eastern wall", "east wall", "opening",
            "wide opening"}),
        "The eastern wall has been left fairly plain, distinguished " +
        "only by single wide opening which leads into the hallway " +
        "beyond.\n");
    add_item( ({"west", "west wall", "western wall"}),
        "A tall carving of Eru Illuvatar pulls your eye as it graces " +
        "the middle of the western wall.\n");
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
    add_item( ({"carving", "relief", "carved relief", "statue", "eru",
            "illuvatar", "eru illuvatar"}),
        "This carving has been masterfully crafted, depicting Eru " +
        "Illuvatar in the finest detail. Protruding out from the " +
        "western wall, the carving almost looks like a separate " +
        "statue, but close inspection shows that it is firmly " +
        "part of the wall. The grey stone has been carefully and " +
        "cleverly honed and polished in different parts of the " +
        "carving to depict tone and shade where none would exist " +
        "otherwise.\n");

    set_no_exit_msg( ({"northwest", "northeast", "southwest",
            "southeast", "east", "north", "south"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");

    add_npc(CA_NPC_DIR + "ca_officer");
    add_npc(CA_NPC_DIR + "ca_soldier", 1 + random(2));

    add_prop(ROOM_I_INSIDE,1);

    add_exit(CABASE_DIR + "hall6", "east", 0, 0, 0);

    reset_room();
}

string
desc()
{
    write("You are in some barracks down in the lower levels of Cair " +
        "Andros. It is clear that a couple dozen of soldiers sleep " +
        "here, as their bunks are lined up neatly across the northern " +
        "and southern walls. However, what really catches your eye " +
        "is a carved relief of Eru Illuvatar which protrudes out " +
        "from the middle of the western wall. The hallway is visible " +
        "through the wide opening in the eastern wall.\n");
}