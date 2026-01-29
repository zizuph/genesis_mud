/*
 * Basement in Cair Andros
 * /d/Gondor/anorien/cairandros/basement/ba9.c
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
        "A long shelf of grey stone runs along the eastern wall. " +
        "It appears to be filled with the remains of old books.\n");
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
    add_item( ({"leather", "paper", "wood", "scraps", "remains"}),
        "You spot what appears to be the remains of some old books. " +
        "Mostly it appears to be old scraps of leather or wood " +
        "that were used as book covers, but there are still some " +
        "badly damaged papers left behind as well.\n");

    set_no_exit_msg( ({"northwest", "northeast", "southwest",
            "southeast", "east", "north", "south"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");

    room_add_object(AN_OBJ_DIR + "bshelf");

    add_npc(CA_NPC_DIR + "ca_officer");
    add_npc(CA_NPC_DIR + "ca_soldier", 1 + random(2));

    add_prop(ROOM_I_INSIDE,1);

    add_exit(CABASE_DIR + "hall6", "west", 0, 0, 0);

    reset_room();
}

string
desc()
{
    write("You are in the lower levels of Cair Andros, standing in " +
        "the sleeping quarters designated for the soldiers who are " +
        "currently serving Gondor by manning the fortress here. The " +
        "north and south walls are both filled with rows of bunks, " +
        "nothing more than simple pallets really. The eastern wall " +
        "has a long stone shelf running from one end of the room to " +
        "the other, mostly containing old scraps of wood, leather and " +
        "paper. A wide opening in the west wall leads back out to " +
        "the hallway.\n");
}