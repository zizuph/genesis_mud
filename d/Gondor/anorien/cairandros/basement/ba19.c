/*
 * Basement in Cair Andros
 * /d/Gondor/anorien/cairandros/basement/ba19.c
 *
 * Varian - February, 2020
 */

#pragma strict_types

#include "../../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit ANORIEN_STD_DIR + "bsmt_base";

int do_pell(string str);

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
        "There is an open space cleared up against the northern " +
        "wall, where someone has erected a sturdy looking sword " +
        "pell along with a collection of practice swords to use " +
        "with it.\n");
    add_item( ({"west", "west wall", "western wall"}),
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
    add_item( ({"pell", "sword pell", "sturdy pell",
            "sturdy sword pell"}),
        "This sturdy looking sword pell has been constructed from " +
        "a thick pole of wood, with some thick leather wrapped " +
        "around it. The pell is about the height of a tall man, " +
        "with stubby protrusions where arms would be. There " +
        "are some practice swords on the ground here which are " +
        "used to practice on the pell.\n");
    add_item( ({"practice sword", "practice swords", "sword",
            "swords"}),
        "There are several smoothly polished lengths of wood here, " +
        "carefully weighted and balanced to mimic the feel of " +
        "a real sword. These practice swords have clearly been " +
        "designed to be used on the sword pell here.\n");
    add_item( ({"pole", "wooden pole", "leather", "thick leather"}),
        "The pole is about eight inches in diameter and over "+
        "six feet tall. A thick wrapping of leather covers " +
        "the upper part of the pole, and you are quite " +
        "certain this has been designed as a sword pell.\n");
    add_item( ({"protrustions", "stubby protrustions", "stubs"}),
        "Two stubby protrusions of wood stick out from the " +
        "sword pell, approximately around shoulder height " +
        "on a tall man. This seems to give the sword pell " +
        "the basic look of a human opponent.\n");

    set_no_exit_msg( ({"northwest", "northeast", "southwest",
            "southeast", "east", "north", "west"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");

    add_npc(CA_NPC_DIR + "ca_officer");
    add_npc(CA_NPC_DIR + "ca_soldier", 1 + random(2));

    add_prop(ROOM_I_INSIDE,1);

    add_exit(CABASE_DIR + "wcor1", "south", 0, 0, 0);

    reset_room();
}

string
desc()
{
    write("This room, like many others down in the lower levels " +
        "of Cair Andros, appears to be sleeping quarters for many " +
        "of the soldiers who have been stationed at the fort. " +
        "Dozens of beds have been lined up in regular intervals " +
        "along both the east and west walls, little more than " +
        "simple pallets for the men to sleep on. Some space has " +
        "been cleared in front of the northern wall, and a sturdy " +
        "sword pell has been erected there. A wide opening in " +
        "the southern wall leads out into the corridor you came " +
        "in from.\n");
}

public int
do_pell(string str)

{
    if(!strlen(str))
    {
        notify_fail("Practice with what, the sword pell?\n");
        return 0;
    }

    if((str != "sword pell") && (str != "the sword pell") && 
        (str != "pell") && (str != "with the pell") &&
        (str != "with sword pell") && (str != "the pell") &&
        (str != "with the sword pell") && (str != "with pell"))
    {
        notify_fail("Practice with what, the sword pell?\n");
        return 0;
    }

    write("You pick up a practice sword and train through " +
        "a series of forms against the pell.\n\nYou feel " +
        "a little better about your skill with a sword.\n");
    SAYBB(" picks up a practice sword and attacks the " +
        "sword pell.\n");

    return 1;
}

public void
init()
{   
    ::init();
    add_action(do_pell, "practice");
}