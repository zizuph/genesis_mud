/*
 * Basement in Cair Andros
 * /d/Gondor/anorien/cairandros/basement/ba5.c
 *
 * Varian - February, 2020
 */

#pragma strict_types

#include "../../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit ANORIEN_STD_DIR + "bsmt_base";
inherit "/d/Gondor/common/lib/drink_water.c";

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
        "An ornate stone pool sits in front of the eastern wall, " +
        "with a simple fountain bubbling fresh water from the top.\n");
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
    add_item( ({"pool", "ornate stone pool", "stone pool",
            "ornate pool"}),
        "An ornate stone pool sits in front of the eastern wall, " +
        "with a simple fountain bubbling fresh water from the top. " +
        "You could probably get a drink here if you were thirsty.\n");
    add_item( ({"fountain", "simple fountain"}),
        "This simple fountain sits in the middle of an otherwise " +
        "ornate stone pool. The fountain keeps circulating the " +
        "water in the pool, keeping the water fresh for " +
        "drinking.\n");

    set_no_exit_msg( ({"northwest", "northeast", "southwest",
            "southeast", "east", "north", "south"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");

    set_drink_from( ({"pool", "fountain", "stone fountain",
        "stone pool"}) );

    add_npc(CA_NPC_DIR + "ca_officer");
    add_npc(CA_NPC_DIR + "ca_soldier", 1 + random(2));

    add_prop(ROOM_I_INSIDE,1);

    add_exit(CABASE_DIR + "hall3", "west", 0, 0, 0);

    reset_room();
}

string
desc()
{
    write("You are in a room designed to house the soldiers who " +
        "have been assigned duty here at the fortress of Cair " +
        "Andros. The lower levels of the fort seem to be filled " +
        "with rooms like this one, where simple beds line the " +
        "north and south walls. Built into the eastern wall, " +
        "this particular room has a pool, ornately carved from " +
        "grey stone, boasting a simple fountain in the middle. " +
        "A steady stream of water bubbles out of the fountain, " +
        "providing a constant source of fresh water. In the " +
        "middle of the west wall, a wide opening spills out " +
        "into the hallway beyond.\n");
}

public void
init()
{   
    ::init();
    init_drink();
}

public void
drink_message(string from)
{
    write("You lean forward and scoop out some fresh water " +
        "from the stone pool. Ahh, refreshing!\n");
    say(QCTNAME(TP) + " leans forward to drink some water " +
        "out of the stone pool.\n");
}