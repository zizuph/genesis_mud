#include "defs.h"

CONSTRUCT_ROOM {
    set_short("Western Entry Hall");
    set_long(
	"You are standing in the northern part of the huge Western Entry Hall.\n" +
	"The northern part of the Hall leads eastwards and westwards. " +
	"The hall itself is in utter darkness@@desc_columns@@ ");
    add_item(({ "wall", "walls"}),
	     "Which wall, the north or south wall?");
    add_item(({ "columns", "column", "south wall", "southern wall" }), 
	     "@@exa_columns@@");
    add_item(({ "north wall", "northern wall" }),
	     "This northern wall seems to be a definite wall. It is solid as the rock, " +
	     "granite, hard and pure granite.");
    WEST("entrhall11");
    EAST("entrhall13");
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
	    ", heavily indeed it lies upon this hall of Dwarven Craft in the Mines of Moria.";
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
    add_action("do_s", "south");
}

int do_s(string arg)
{
    if (strlen(arg))
	return 0;
    TP->move_living("south", THIS_DIR + "entrhall22");
    return 1;
}
