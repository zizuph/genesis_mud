/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * path.c (to the beach)
 *
 */

#include "/d/Terel/include/Terel.h"
inherit PORT_DIR + "port_room";

static object shovel;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Path outside fence");
    set_long("You are standing on a muddy path just outside " +
	     "a tall fence. The path " +
	     "continues in the southeast and west directions. " +
	     "The wooden fence to the west, where there also " +
	     "seems to be some kind of gate in it. To the southeast " +
	     "you catch a glimpse of a sandy beach. " +
	     "There is some brushwood to the north which " +
	     "effectively blocks any passage. " +
	     "There is a distinct smell in the air.\n");
    
    add_item(({"fence", "wooden fence"}), 
	     "This is the eastern part of the tall wooden fence that " +
	     "surrounds this village. It was built to protect the " +
	     "village people from the creatures in the forest north of " +
	     "here. There is a gate in the fence just west from here.\n");
    
    add_item(({"gate"}), 
	     "It looks as if the gate is opened, but you must go " +
	     "closer to be sure of that.\n");

    add_item(({"beach", "sandy beach"}), "It looks pretty inviting.\n");

    add_item(({"brushwood"}), "It is very thick. One can probably " +
	     "hide an army here without anybody noticing it.\n");

    add_exit(PORT_DIR + "beach/b1", "southeast", 0);
    add_exit(PORT_DIR + "e_gate",   "west", 0);

    add_prop(OBJ_I_SEARCH_TIME, 20);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
}

public string
do_search(object searcher, string str)
{
    if (str != "brushwood") return "";

    if (shovel) return "";

    seteuid(getuid());

    shovel = clone_object(PORT_DIR + "obj/shovel");

    if (shovel->move(searcher)) {
	shovel->move(this_object());
    }

    return "You find a " + shovel->short() + " hidden in the " +
	   "brushwood.\n";   
}
