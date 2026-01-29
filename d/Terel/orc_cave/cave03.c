/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave03.c
 *
 * The batcave.  Here the player may obtain batshit for the batshit quest.
 */

#include "/d/Terel/include/Terel.h"
inherit ORC_CAVE_DIR + "cave_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Batcave");
    set_long(query_long() +
	     "High pitched squealing sounds can be heard from the bats "+
	     "hanging in the high ceiling. The ground is covered with "+
	     "lumps of bat droppings.\n");
  
    DARK;
    
    add_item("bat droppings",
	     "There are a lot of small lumps of bat " +
	     "droppings here. A more educated person than you would call " +
	     "them batguano, on the other hand that educated person would " +
	     "never try picking them either.\n");

    add_item(({"bat", "bats"}),
	     "They hang from the ceiling, much too high for you to reach " +
	     "them.\n");
    
    add_cmd_item(({"batguano", "bat droppings", "lumps of bat droppings"}),
		 ({"smell", "pick"}),
		 ({"The batguano smells like shit from a bat.\n", "@@pick"}));
    
    add_exit(ORC_CAVE_DIR + "cave02", "west");    
    add_exit(ORC_CAVE_DIR + "cave05", "south");
    add_exit(ORC_CAVE_DIR + "cave14", "north");
}

/*
 * Function name: pick
 * Description:   Handle pick action for the batshit cmditem
 * Returns:       1/0
 */
public int
pick()
{
    object ob;
    object batshit;

    if (TP->query_prop("picked_shit")) {
	NF("You don't find a good piece of batguano, so you stop looking.\n");
	return 0;
    }
    
    write("With a wince you pick up a good looking piece of batguano and "+
	  "put it in your pocket.\n");
    
    FIX_EUID;
    batshit = clone_object(ORC_CAVE_DIR + "obj/batshit");
    batshit->add_prop("_shit_picker", TP->query_name());
    batshit->move(TP);
    TP->add_prop("picked_shit", 1);
    say(QCNAME(TP)+" gently picks a lump of bat dropping.\n");
    return 1;
}

/*
 * Function name: smell_desc
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */ 
public string
smell_desc()
{
    return "The reek of bats and bat droppings is in the air.\n";
}
