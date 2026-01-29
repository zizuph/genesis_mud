#include "defs.h"

CONSTRUCT_ROOM {
    set_short("Eastern part of Western Entry Hall");
    set_long(
	"Eastern part of the Western Entry Hall.\n" +
	"In the darkness to the west, the central doorway frames an " +
	"entry onto an arched passage, @@desc_columns@@ "+
	"The Central Doorway is in the east leading to Durin's Road, " +
	"the main Avenue leading through the Mines of Moria into the " +
	"City of Khazad-dum.");
    add_item(({ "wall", "walls"}),
	     "Which wall, the north or the south wall?");
    add_item(({ "columns", "north wall", "northern wall",
		"column", "south wall", "southern wall" }), 
	     "@@exa_columns@@");
    add_item("passage", "Which passage? East or West?");
    add_item(({ "east passage", "doorway", "eastern doorway",
	        "durin's way", "avenue", "durin's road", "road"}),
	     "It seems to lead to Durin's Road, the main passage " +
	     "of the Mines of Moria. This Road used to be used by " +
	     "Elves and Humans which wanted to cross the Misty Mountains.");
    add_item(({ "west passage", "arched passage", "central doorway"}),
	     "It leads into the arched passage down to the stairs, " +
	     "and the Western Gate of Moria.");
    WEST("entrhall22");
    EAST("durin-1");
}

string 
desc_columns()
{
    if (CAN_SEE_IN_ROOM(TP) > 1)
	return 
	    "and two lines of thick, square columns divide this hall and, "+
	    "in the dark, one might not realize that the passage is " +
	    "interupted.";
    else
	return 
	    "which probably leads to the Western Gate.";
}

string
exa_columns()
{
    if (CAN_SEE_IN_ROOM(TP) > 1)
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
    TP->move_living("north", MINES_DIR + "entrhall13");
    return 1;
}

int do_s(string arg)
{
    if (strlen(arg))
	return 0;
    TP->move_living("south", MINES_DIR + "entrhall33");
    return 1;
}

