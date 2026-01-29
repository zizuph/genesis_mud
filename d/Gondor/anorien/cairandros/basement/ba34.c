/*
 * Basement in Cair Andros
 * /d/Gondor/anorien/cairandros/basement/ba34.c
 *
 * A lesser magic ring can be found here.
 *
 * Varian - March, 2020
 */

#pragma strict_types

#include "../../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit ANORIEN_STD_DIR + "bsmt_base";
inherit "/lib/unique";

int ring_found = 0;
int last_time = 0;

void
reset_room()
{
    ring_found = 0;
}

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
    add_item( ({"west", "western wall", "west wall"}),
        "Much like the eastern wall, there are several beds lined " +
        "up against the stone blocks of the western wall. The beds " +
        "are really not much more than pallets, wooden boxes " +
        "filled with straw covered with a thick layer of linen.\n");
    add_item( ({"north", "northern wall", "opening", "wide opening",
            "north wall"}),
        "The northern wall has been left fairly plain, distinguished " +
        "only by single wide opening which leads into the hallway " +
        "beyond.\n");
    add_item( ({"south", "southern wall", "south wall"}),
        "The southern wall here is mostly covered by a tall stack of " +
        "large open boxes, each filled with thick coils of rope.\n");
    add_item( ({"east", "eastern wall", "east wall"}),
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
    add_item( ({"large boxes", "open boxes", "large open boxes",
            "boxes", "stack", "tall stack"}),
        "There is a tall stack of open boxes piled up against the " +
        "south wall, all filled with long, thick coils of sturdy " +
        "rope.\n");
    add_item( ({"coil", "thick coil", "thick coils", "rope", "coils",
            "thick rope", "thick coil of rope", "thick coils of rope",
            "coil of rope", "coils of rope"}),
        "There are probably hundreds of coils of thick rope stored " +
        "in the boxes here. You know what they say about rope: " +
        "'You'll want it, if you haven't got it!'\n");

    add_cmd_item(({"stone", "block", "stone block"}),
        "wriggle", "@@pull_stone");

    set_no_exit_msg( ({"northwest", "northeast", "southwest",
            "southeast", "east", "west", "south"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");

    add_npc(CA_NPC_DIR + "ca_officer");
    add_npc(CA_NPC_DIR + "ca_soldier", 1 + random(2));

    add_prop(ROOM_I_INSIDE,1);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    add_exit(CABASE_DIR + "ecor3", "north", 0, 0, 0);
    
    reset_room();
}

string
desc()
{
    write("Similar to most of the other rooms in the lower levels " +
        "of this fortress, this room has been set aside as sleeping " +
        "quarters for the soldiers here at Cair Andros. There are " +
        "dozens of bunks, simple pallets which serve as beds for the " +
        "men, which have been lined up in tidy rows along both the " +
        "east and west walls. The southern wall is covered by a " +
        "tall stack of open boxes filled with thick coils of rope " +
        "while a wide opening in the northern wall leads back out " +
        "to the corridor you enter in from.\n");
}

string
pull_stone()
{
    object gold_ring;

    if (last_time + 10 > time())
    {
        write("You try to loosen the stone block, but it seems " +
            "to be a little stuck. You might have to try again " +
            "later.\n");
        return "";
    }

    last_time = time();

    if (!ring_found) 
    {    
        ring_found = 1;
        gold_ring = clone_unique(AN_ARM_DIR + "goldring", 1);
    }

    if (gold_ring)
    {
        write("You manage to wriggle the stone a little bit.\n");
        gold_ring->move(this_player(), 1);
        write("The stone comes loose from the wall and you find " +
            "a small ring! You quickly push the stone back in " +
            "the wall.\n");
        ring_found = 1;
        return "";
    }

    write("You manage to wriggle the stone a little bit.\nThe stone " +
        "comes loose from the wall, but there is nothing there. You " +
        "push the stone back in the wall.\n");

    return "";
}

public string
do_search(object pl, string arg)
{
    if (member_array(arg,
        ({ "southern wall", 
           "south wall",}) ) == -1)
    {
        return "Your search reveals nothing special.\n";
    }

    return "You find a loose stone block near the base of the " +
        "southern wall! You think you might be able to wriggle it " +
        "out!\n";
}