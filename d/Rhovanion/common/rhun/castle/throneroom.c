
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

init()
{
    ::init();
    add_action("sit", "sit");
}

create_room()
{
    set_short("Throne room");
    set_long("This is the throne room of this ruined castle.  A "+
	"large seat of stone, the throne of whatever lord might "+
	"have reigned here, stands at the north side of the room.  "+
	"The walls are hung with tapestries of red and gold, though "+
	"most of these are faded and tattered.  The only exit lies "+
	"back to the south.\n");

    add_item(({"rug", "rugs", "tapestry", "tapestries", "decoration", 
	"decorations"}), "The rugs and tapestries that decorate "+
	"this chamber were once very fine and colorfully beautiful."+
	"  The passage of time has left little behind of them that "+
	"is attractive, however.\n");
    add_item(({"wall", "walls", "stone", "stones", "grey stone"}), 
	"The walls here are made of a light-grey stone.  They have "+
	"begun to crumble in places, due to natural entropy and the "+
	"passage of time.\n");
    add_item(({"chair", "seat", "throne"}), "The throne at the "+
	"head of this room is made entirely of stone.  It looks like "+
	"it was rather uncomfortable for sitting in.\n");
	
    AE(RHUN+"castle/cross","south");

    IN;
}

sit()
{
    write("The only thing here to sit in is the stone throne, and it "+
	"doesn't appear too comfortable.  You decide to remain standing "+
	"instead.\n");
}
