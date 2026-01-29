#include "defs.h"
#include <stdproperties.h>

//object lupe;

CONSTRUCT_ROOM {
    set_short("Behind draperies");
    set_long("You are behind the velvet draperies. There is a broken glass "+
	     "monter with the inscription \"Crown Regalia\" here.\n");
    add_item(({"monter","glass","glass monter","inscription","crown regalia","regalia"}),
	     "It is a broken glass monter which used to hold the royal "+
	     "crown regalia. It is empty now, of course.");
    add_item("draperies",
	     "The velvet draperies hang from high up under the ceiling.");
    EXIT("throne","north");
    //add_prop(OBJ_I_SEARCH_TIME, 4);
    //add_prop(OBJ_S_SEARCH_FUN, "my_search");
    //reset();
}
/*
RESET_ROOM {
    if (!lupe)
	lupe = clone_object(MORIA_OBJ + "mag_glass");
}

mixed
my_search(object tp, string str)
{
    if (member_array(str, ({"monter", "glass", "glass monter", "regalia",
			    "crown regalia"})) >= 0)
	if (lupe) {
	    lupe->move(TO);
	    lupe = 0;
	    return "You found something!\n";
	}

    return 0;
}
*/
