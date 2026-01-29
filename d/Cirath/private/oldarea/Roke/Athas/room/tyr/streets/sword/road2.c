inherit "/std/room";

#include "road.h"
#include <macros.h>

#define COM_STR "/d/Roke/Athas"

create_room()	{

	set_short("Sword street");
	set_long(BSS("You are on Sword Street, the street where the weaponsmith "+
		"and the second hand weapon stores are located. There "+
		"is a forge to the west, and there is a sign hanging "+
		"over the door. The Commoners road is to the southwest.\n"));

	add_item("sign", BSS(
		"The sign is really a huge axe-blade with writing "+
		"on it.\n"));

	add_exit(SWO_STR+"road1","northeast",0);
	add_exit(COM_STR+"xxx","southwest","@@closed");
	add_exit(SHOP_D+"smith","west",0);

}
closed()	{
	write(BSS("Due to building activities, the Commoners "+
		"road is closed. We hope we can have it opened "+
		"again very soon. Sorry for all inconvenience.\n"));
	return 1;
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
    
	write("You read:\n"+BSS(
		"      Tentavva's weapon forge.\n"+
     "We repair weapons in any condition!\n"+
		""));
	say(QCTNAME(this_player())+" reads the large sign.\n");
    return 1;

}
