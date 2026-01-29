#include "defs.h"

CONSTRUCT_ROOM {
    set_short("Center of Western Entry Hall");
    set_long(
	"You are standing in the center of the Western Entry Hall.\n" +
	"In the darkness to the west, the central doorway frames an " +
	"entry onto an arched passage, @@desc_columns@@ "+
	"The Central Doorway is in the east leading to Durin's Road, " +
	"a descending road into the Lower Mines\n");
    add_item(({ "wall", "walls"}),
	     "Which wall, the north or the south wall?");
    add_item(({ "columns", "north wall", "northern wall",
		    "column", "south wall", "southern wall" }), 
	     "@@exa_columns@@");
    add_item("passage", "Which passage? East or West?");
    add_item(({ "east passage", "doorway", "eastern doorway" }),
	     "It seems to lead to the Durin's Road, the main passage " +
	     "of the Mines of Moria.");
    add_item(({ "west passage", "arched passage", "central doorway"}),
	     "It leads into the arched passage down to the stairs, " +
	     "and the Western Gate of Moria.");
    WEST("entrhall21");
    EAST("entrhall23");
}

string 
desc_columns()
{
    if (CAN_SEE_OF_ROOM(TP) > 1)
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
    TP->move_living("north", MINES_DIR + "entrhall12");
    return 1;
}

int do_s(string arg)
{
    if (strlen(arg))
	return 0;
    TP->move_living("south", MINES_DIR + "entrhall32");
    return 1;
}

