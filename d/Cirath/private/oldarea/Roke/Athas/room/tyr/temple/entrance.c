inherit "/std/room";
#include "temple.h"
#include <macros.h>
 
void reset_room()
{
}

create_room()
{

	set_short("Temple entrance");
	set_long(BSS("You have entered the Temple of Tyr, a large "+
		"temple placed in the centre of Tyr, just by the town "+
		"square. The temple itself is dedicated to the humongous "+
		"dragon Karazat, the deity of Tyr. There is a small altar "+
		"here and a important looking wooden sign.\n"));

	add_item(({"wooden sign","sign"}),BSS(
		"The sign has some writing on it, so you might want to read "+
		"it. Now that you look at it, you "+
		"notice that the sign is made out of teak, a material not "+
		"commonly used in the Tyr region, nor able to get close "+
		"to the tyr region and therefore must be imported for the "+
		"making of this sign only. You wonder how anyone can think "+
		"of using so much money on a sign, when there is so much to "+
		"be done.\n"));
add_exit("/d/Roke/gresolle/jab/stoneroom","south");


	add_item(({"altar","small altar"}),BSS(
		"This altar is one of the smallest you have ever seen, "+
		"and you guess it is one they have just placed here so "+
		"that you, and others may pray here while the temple is "+
		"undergoing repairs.\n"));

	add_exit(SQUA_D+"square6","west",0);
	add_exit(TEMP_D+"boardroom","east",0);

    add_prop(ROOM_I_INSIDE, 1);
 
    call_out("reset_room", 1);

}

init()
{
    ::init();
    add_action("do_read","read");
	add_action("do_pray","pray");
}

int
do_read(string str)
{    
    if (!str)
    return 0;

    if (str != "sign")
    {
       notify_fail("What do you want to read ?");
       return 0;
    }
    
	write("You read:\n"+BSS(
		"The temple is not open at the time, because of "+
		"some internal changes. If you need to pray to our "+
		"god, Karazat, that is possible to do by the altar "+
		"here.\n"));
	say(QCTNAME(this_player())+" reads the wooden sign.\n");
    return 1;

}

int
do_pray(string str)
{    
    if (!str)
    return 0;

    if (str != "by altar" && str != "at altar" && str != "altar")
    {
       notify_fail("Where do you want to pray ?");
       return 0;
    }
    
	write(BSS("You kneel down by the altar and joins your "+
		"hands in prayer. You suddelnly feel peace and "+
		"tranquillity, but it passes. You then arise from "+
		"the altar.\n"));
	say(QCTNAME(this_player())+" prays by the small altar.\n");
    return 1;

}
