inherit "/std/room";

#include "road.h"
#include <macros.h>

create_room()	{

	set_short("Sword street");
	set_long(BSS("You are now on Sword Street, the famous street "+
		"of weaponsmiths and shops. There is a second "+
		"hand weaponry to the west, and there is a sign "+
		"hanging over the door.\n"));

	add_item("sign", BSS(
		"It is a rather large sign with some writing on it.\n"));

	add_exit(SWO_STR+"road2","southwest",0);
	add_exit(MGR_STR+"road4","north",0);
	add_exit(SHOP_D+"weapons","west",0);

}
init()
{
    ::init();
    add_action("do_read","read");
}

int
do_read(string str)
{    
    if (!str)
    return 0;

	if (str != "sign")
    {
	notify_fail("What do you want to read?\n");
       return 0;
    }
    
	write("You read:\n"+
		"             Riautar's second hand weapons.\n"+
		"All in fine swords, axes and halberds. Weapons for "+
		"all occassions.\n");
	say(QCTNAME(this_player())+" reads the large sign.\n");
    return 1;

}
