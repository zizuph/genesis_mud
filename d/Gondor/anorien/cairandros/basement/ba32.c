/*
 * Basement in Cair Andros
 * /d/Gondor/anorien/cairandros/basement/ba32.c
 *
 * Varian - March, 2020
 */

#pragma strict_types

#include "../../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit ANORIEN_STD_DIR + "bsmt_base";

int do_read(string str);

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
    add_item( ({"west", "west wall", "western wall"}),
        "Much like the eastern wall, there are several beds lined " +
        "up against the stone blocks of the western wall. The beds " +
        "are really not much more than pallets, wooden boxes " +
        "filled with straw covered with a thick layer of linen.\n");
    add_item( ({"north", "northern wall", "north wall", "opening",
            "wide opening"}),
        "The northern wall has been left fairly plain, distinguished " +
        "only by single wide opening which leads into the hallway " +
        "beyond.\n");
    add_item( ({"south", "south wall", "southern wall"}),
        "A marble statue of a mounted warrior stands in the middle " +
        "of the southern wall.\n");
    add_item( ({"east", "east wall", "eastern wall"}),
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
    add_item( ({"statue", "marble statue", "warrior", "marble warrior",
            "mounted warrior", "marble", "rider", "rider of rohan"}),
        "This statue has been carved entirely out of a white marble " +
        "and it is a life-sized depiction of a mounted soldier. A " +
        "closer inspection shows that the statue is actually " +
        "depicting a Rider of Rohan, and a small inscription " +
        "makes it clear that it was a friendship gift to Gondor.\n");
    add_item( ({"inscription", "small inscription"}),
        "The inscription reads:\n\nTo our eternal friends in " +
        "Gondor who guard the Anduin at Cair Andros.\n\nThengel " +
        "of Rohan - T.A. 2955\n");

    set_no_exit_msg( ({"northwest", "northeast", "southwest",
            "southeast", "east", "west", "south"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");

    add_npc(CA_NPC_DIR + "ca_officer");
    add_npc(CA_NPC_DIR + "ca_soldier", 1 + random(2));

    add_prop(ROOM_I_INSIDE,1);

    add_exit(CABASE_DIR + "ecor2", "north", 0, 0, 0);

    reset_room();
}

string
desc()
{
    write("You are in the barracks that fill the lower levels " +
        "of Cair Andros. Dozens of beds line the east and west " +
        "walls here, making this part of the sleeping quarters " +
        "for the men who serve in the fort. A marble statue " +
        "of a mounted warrior catches your eye as it stands in " +
        "front of the southern wall, while the corridor is " +
        "visible through the wide opening in the northern wall.\n");
}

public int
do_read(string str)

{
    if(!strlen(str))
    {
        notify_fail("What did you want to read?\n");
        return 0;
    }

    if((str != "the inscription") && (str != "small inscription") &&
        (str != "inscription") && (str != "the small inscription"))
    {
        notify_fail("Read what, the inscription?\n");
        return 0;
    }

    write("The inscription reads:\n\nTo our eternal friends in " +
        "Gondor who guard the Anduin at Cair Andros.\n\nThengel " +
        "of Rohan - T.A. 2955\n");
    SAYBB(" reads the inscription on the statue.\n");

    return 1;
}

public void
init()
{   
    ::init();
    add_action(do_read, "read");
}