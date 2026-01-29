
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"
#include <stdproperties.h>
#include <macros.h>

init()
{
    ::init();
    add_action("search_floor", "search");
    add_action("trap_door", "enter");
}

create_room()
{
    set_short("Hut");
    set_long("This is a simple hut, the home of some of the "+
	"simple people of Rhosgobel.  It is sparsely furnished.  "+
	"Really,  there's nothing very interesting here.  Unlike "+
	"some of the other huts in town, this one has a planked "+
	"wooden floor.  You wonder at the difference.  The "+
	"door stands leading back to the west.\n");

    AE(RHOS+"road1", "east");
    
    IN;
    
    add_item("floor", "You gaze at the wooden floor in wonderment, "+
	"because it is so different from the other huts in town.  "+
	"Perhaps you should search along it...\n");
}

int
search_floor(string str)
{
    NF("Search what?\n");
    if(!strlen(str))
	return 0;
    if((str=="floor")||(str=="wooden floor"))
    {
	write("Searching along the floor, you located a "+
	    "secret trap door which you think you can enter!\n");
	return 1;
    }
    return 0;
}

int
trap_door(string str)
{
    NF("Enter what?\n");
    if((!strlen(str))||((str!="door")&&(str!="trap door")))
	return 0;
    else
    {
	write("You descend down into the room beneath the "+
	    "trap door.\n");
	say(QCTNAME(TP)+" descends through a trap door in "+
	    "the floor.\n");
	TP->move_living("M", RHOS+"secret_room");
    return 1;
    }
}
