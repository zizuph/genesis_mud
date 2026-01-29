#include "defs.h"

CONSTRUCT_ROOM {
    set_short("Western Entry Hall");
    set_long(
	"The Western Entry Hall.\n" +
	"You are standing in the north-east corner of the First Hall in the Western " +
	"Mines of Moria. Here you notice that there is an exit leading up and a little " +
	"bit to the north-east in the eastern Wall. The passage is arched with a definite " +
	"Black and White theme, the stones probably being marble and black granite. " +
	"The Hall extends in the western direction@@desc_columns@@ ");

    add_item(({ "wall", "walls"}),
	     "Which wall, the north, south or east wall?");
    add_item(({ "columns", "column", "south wall", "southern wall" }), 
	     "@@exa_columns@@");
    add_item(({ "north wall", "northern wall" }),
	     "This northern wall seems to be a definite wall. It is solid as the rock, " +
	     "granite, hard and pure granite.");
    add_item(({ "east wall", "eastern wall", "arched passage", "passage" }),
	     "The eastern wall have one noticable feature, the arched passage which " +
	     "seems to traverse slightly upwards to the north-east.");
    WEST("entrhall12");
    EAST("opal-road-1");
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
	    ", and in the far western end you can outline another exit.";
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
    TP->move_living("south", THIS_DIR + "entrhall23");
    return 1;
}
