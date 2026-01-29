#include "defs.h"

CONSTRUCT_ROOM {
    set_short("You are surrounded by dirty blocks.");
    set_long("You are surrounded by dirty blocks. The place is so crowded "+
	     "that you cannot possibly figure from where you came, nor "+
	     "find any other obvious exits.\n"
    );
    add_item(({"blocks","exits"}), "You see nothing special.");
    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN,  "search_fun");
    EXIT("dome","east");
/*
    EXIT("dwarf","north");
    EXIT("behblock","west");
*/
}

init() {
    ::init();
    add_action("do_north", "north");
    add_action("do_west",  "west");
}

int
do_north(string str)
{
    if (!str||str=="") {
	this_player()->move_living("north", THIS_DIR+"dwarf");
	return 1;
    }
}

int
do_west(string str)
{
    if (!str||str=="") {
	TP->move_living("west", THIS_DIR+"behblock");
	return 1;
    }
}

string
search_fun(object who, string what)
{
    if (what == "blocks" || what == "block" || 
	what == "exits" || what == "exit") 
	{
	    return "You see that it is possible to go west and north here!\n";
	}
    else
	return 0;
}
		    
