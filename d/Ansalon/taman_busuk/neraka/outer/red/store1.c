/* Carridin */

#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit OUTER_IN;

object shopkeeper;

void
reset_neraka_room()
{
	if (!objectp(shopkeeper))
		shopkeeper =clone_npc(NNPC + "lute");
}

void
create_neraka_room()
{	
	set_short("Inside a pawnshop");
	set_long("You are inside a pawnshop called \"Lute's Loot\". " +
		"@@lute_here@@\n");

	add_item_inside();
	add_item(({"counter", "large counter"}),"It's a large wooden counter in " +
		"good repair from behind which the proprietor runs the pawnshop.\n");
     
	add_exit(NOUTER+"red/r16","northwest","@@msg@@",0,0);
	add_exit(NOUTER+"red/store_room1","south","@@wiz_check",1,1);
   
	reset_room();
}

int
msg()
{
    write("You step out of the pawnshop and out on the market square.\n");
    return 0;
}

string
lute_here()
{
	if(!present("neraka_lute"))
	{
		return "A large counter stands at the back of the room, and behind it " +
			"you see the exit to the storeage room. The proprietor, however, is " +
			"nowhere to be seen. If you wish to trade, you must return later.";
	}
	else
	{
		return "Behind the large counter at the back of the room stands a small " +
			"man, cautiously watching you. Behind the counter lies the exit to " +
			"the storage room.";
	}
}

int
wiz_check()
{
    if (this_player()->query_wiz_level())
        return 0;
    write("You are not allowed inside the storeroom.\n");
    say(QCTNAME(this_player()) + " tries to go south but fails.\n");
    return 1;
}
