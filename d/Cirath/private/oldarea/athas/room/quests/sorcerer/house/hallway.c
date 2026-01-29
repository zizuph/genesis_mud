inherit "/std/room";

#include <stdproperties.h>
#include "/d/Roke/common/defs.h"
#include <macros.h>
 
create_room()
{
 
    set_short("Light halway");
	set_long(BSS("You are in a nice looking hallway with the kitchen "+
		"east, the sitting room west and a guest room north. "+
		"the hallway is lit by a small lamp.\n"));

    add_prop(ROOM_I_INSIDE, 1);
 
	add_exit(HOUS_D+"guestroom","north",0);
	add_exit(HOUS_D+"kitchen","east",0);
	add_exit(HOUS_D+"sittroom","west",0);

	add_item(({"lamp","small lamp"}),BSS(
			"This is a cute little oil-lamp, just as you have"+
		" heard about from faerytales.\n"));
}

init()
{
    ::init();
    add_action("do_rub","rub");
}

int
do_rub(string str)
{    
    if (!str)
    return 0;

    if (str != "lamp")
    {
	notify_fail("What would you like to rub, you said ?\n");
       return 0;
    }
    
	write("When you rub the lamp, you feel some divine presence, telling "+
		"you:\n	   'Fireplaces can hide so many things.'\n\n"+
		"Then you notice the little djinni that pops back into the lamp.\n");
    say(QCTNAME(this_player())+" rubs a small lamp, that stands here to "+
                "light the hallway.\n");
    return 1;

}
