#include "defs.h"

CONSTRUCT_ROOM {
    set_short("Western Entry Hall");
    set_long(
	"You are standing in a huge hall called the Western Entry Hall.\n" +
	"To the west, the central doorway frames an entry onto an arched " +
	"passage which leads to the stairway down to the West Gate. The " +
	"hall itself roams in the Darkness@@desc_columns@@ "+
	"You can continue east towards a Central Doorway which looks " +
	"onto a wide road, the main passage of the Mines of Moria, " +
	"also called Durin's Road.\n");
    add_item(({ "wall", "walls"}),
	     "Which wall, the north, south or west wall?");
    add_item(({ "west wall", "western wall"}),
	     "The wall seems to be of solid granite, and the only " +
	     "exit seems to be into the western arched passage.");
    add_item(({ "columns", "north wall", "northern wall",
		    "column", "south wall", "southern wall" }), 
	     "@@exa_columns@@");
    add_item("passage", "Which passage? East or West?");
    add_item(({ "east passage", "doorway", "eastern doorway" }),
	     "It seems to lead to Durin's Road, the main passage " +
	     "of the Mines of Moria.");
    add_item(({ "west passage", "arched passage", "central doorway"}),
	     "It leads into the arched passage down to the stairs, " +
	     "and the Western Gate of Moria.");
    WEST("stair2");
    EAST("entrhall22");
}

string 
desc_columns()
{
    if (CAN_SEE_OF_ROOM(TP) > 1)
	return 
	    ", and two lines of thick, square columns divide this hall and, "+
	    "in the dark, one might not realize that the passage is " +
	    "interupted.";
    else
	return 
	    ", heavily indeed it lies upon this Hall.";
}

string
exa_columns()
{
    if (CAN_SEE_OF_ROOM(TP) > 1)
	return
	    "The lines of column are very thick, but you notice that, " +
	    "you can leave north or south through the columns if you " +
	    "wanted.";
    else
	return 
	    "The wall seems to be thick, probably made of black basalt.";
}

init()
{
    ::init();
    add_action("do_n", "north");
    add_action("do_s", "south");
}

int do_n(string arg)
{
    if (strlen(arg))
	return 0;
    TP->move_living("north", THIS_DIR + "entrhall11");
    return 1;
}

int do_s(string arg)
{
    if (strlen(arg))
	return 0;
    TP->move_living("south", THIS_DIR + "entrhall31");
    return 1;
}
