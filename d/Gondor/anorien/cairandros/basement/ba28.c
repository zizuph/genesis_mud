/*
 * Basement in Cair Andros
 * /d/Gondor/anorien/cairandros/basement/ba28.c
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
    add_item( ({"south", "south wall", "southern wall"}),
        "A narrow doorway sits in the middle of the southern wall.\n");
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
    add_item( ({"door", "narrow door", "doorway", "narrow doorway"}),
        "You peek through the narrow doorway in the southern wall and " +
        "see a couple of wide stone steps leading down to a small " +
        "stone landing that has a small berth on the Anduin. Thick " +
        "metal bars from a portcullis currently block access from " +
        "the landing to the river however.\n");
    add_item( ({"landing", "stone landing", "portcullis", "bars",
            "metal bars", "thick bars", "thick metal bars"}),
        "This stone landing has a portcullis with thick metal bars " +
        "guarding the far side where it meets the Anduin. It looks " +
        "like the landing serves as a berth for a small boat that " +
        "could launch into the river from here.\n");
    add_item( ({"boat", "small boat"}),
        "There are currently no boats here, small or otherwise.\n");
    add_item( ({"steps", "step", "wide stone steps", "wide steps",
            "wide stone step", "stone step", "stone steps",
            "wide step"}),
        "There are two wide steps made of stone here, they lead " +
        "down towards a stone landing visible through the doorway " +
        "in the southern wall.\n");
    add_item( ({"berth", "river", "water", "anduin", "anduin river"}),
        "It looks like the landing you can see is designed to act " +
        "as a berth for a boat to launch into the Anduin river. The " +
        "water looks placid and still here, and the stone " +
        "foundation of the fort blocks you from seeing the western " +
        "shore or even the rest of the river from here. You get " +
        "the feeling that this exit would be almost invisible if " +
        "someone was to look at the fort from outside.\n");

    set_no_exit_msg( ({"northwest", "northeast", "southwest",
            "southeast", "east", "west", "south"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");

    add_npc(CA_NPC_DIR + "ca_officer");
    add_npc(CA_NPC_DIR + "ca_soldier", 1 + random(2));

    add_prop(ROOM_I_INSIDE,1);

    add_exit(CABASE_DIR + "wcor5", "north", 0, 0, 0);

    reset_room();
}

string
desc()
{
    write("You are inside the sleeping quarters of some barracks " +
        "designed for the soldiers serving their duty here in " +
        "Cair Andros. Dozens of beds are stacked up along both " +
        "the east and west walls here, providing nothing more " +
        "than the basic needs for soldiers to rest. A narrow " +
        "doorway opens up in the southern wall, while the " +
        "corridor you came in from is clearly visible through a " +
        "wide opening that breaks through the northern wall.\n");
}