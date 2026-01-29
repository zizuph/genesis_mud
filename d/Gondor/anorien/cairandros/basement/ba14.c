/*
 * Basement in Cair Andros
 * /d/Gondor/anorien/cairandros/basement/ba14.c
 *
 * Varian - February, 2020
 */

#pragma strict_types

#include "../../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit ANORIEN_STD_DIR + "bsmt_base";

int do_grab(string str);
int torches_left = 5;

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
        "A tall stack of firewood has been piled up against the " +
        "western wall here.\n");
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
    add_item( ({"wood", "firewood", "stack", "pile"}),
        "This large stack of firewood has been piled up against the " +
        "west wall, giving the soldiers of the fort plenty of " +
        "fuel for warming up on chilly nights. If you were looking " +
        "to grab a torch, you think that there might be something " +
        "suitable in the pile.\n");

    set_no_exit_msg( ({"northwest", "northeast", "southwest",
            "southeast", "east", "north", "south"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");

    add_npc(CA_NPC_DIR + "ca_officer");
    add_npc(CA_NPC_DIR + "ca_soldier", 1 + random(2));

    add_prop(ROOM_I_INSIDE,1);

    add_exit(CABASE_DIR + "hall8", "east", 0, 0, 0);

    reset_room();
}

string
desc()
{
    write("You are currently visiting the lower levels of Cair " +
        "Andros where most of the sleeping quarters for the soldiers " +
        "stationed in this fortress. Plenty of beds line the walls " +
        "at the north and south ends of the room, while a large " +
        "stack of firewood has been piled up high against the " +
        "western wall. You can see the hallway on the other side " +
        "of a wide opening that breaks through the grey stone of " +
        "the eastern wall.\n");
}

/*
 * Function name:        do_grab
 * Description  :        Allows someone to grab a torch from the 
 *                       pile of firewood.
 * Returns      :        int 0 - Prompt for proper syntax
 *                       int 1 - Returns the emote and a torch
 */

public int
do_grab(string str)
{
    object torch;
    notify_fail("Grab what? A torch?\n");
    
    if((str != "torch" && str != "a torch"))
        return 0;
        
    if (torches_left < 1)
        {
            write("You look all around, but there are no pieces " +
                "of firewood suitable for use as a torch.\n");
            return 1;
        }
            
            setuid();
            seteuid(getuid());
            torch = clone_object("/d/Gondor/common/obj/torch");
            torch->move(this_player(), 1);
            write("You find a piece of wood that could serve as a " +
                "torch.\n");
            say(QCTNAME(TP) + " grabs a torch from the pile of " +
                "firewood.\n");
            torches_left = torches_left -1;

        return 1;
}

public void
init()
{   
    ::init();
    add_action(do_grab, "grab");
}