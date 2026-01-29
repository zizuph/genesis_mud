inherit "/std/room";
#include "road.h"
#include <macros.h>

#define COM_STR "/d/Roke/Athas"

reset_room()
{
}
 
create_room()
{

	set_short("Shield street");
	set_long(BSS("You are standing on the south end of Shield street, "+
		"the street with the famous armourer Hilmer, "+
		"who studied under Calmacil, the master armourer of "+
		"Gondor for many years. You enter the Commoners "+
		"road to the south, and you can follow the Shield "+
		"street further north. Outside the forge to the "+
		"west there is a large sign.\n"));

	add_item(({"sign","large sign"}), BSS(
		"This large sign is made upon a huge armour piece, "+
		"hanging from a pole on the wall. There are some "+
		"engravings on it, so maybe you should read it.\n"));
 
    add_prop(ROOM_I_INSIDE, 0);

	add_exit(COM_STR+"road3","south","@@closed");
	add_exit(SHI_STR+"road1","north",0);
	add_exit("/d/Gondor/Roke/Athas/armoury","west",0);

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
		"    Hilmer, the Master armourer of Tyr.\n")+
		"All in armours and shields for sale!\n");
	say(QCTNAME(this_player())+" reads the large sign.\n");
    return 1;

}
