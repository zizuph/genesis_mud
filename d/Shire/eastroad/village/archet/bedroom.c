#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
inherit SHIRE_DIR +"room";

//object man;

create_room()
{
	set_short("A bedroom");
	set_long(
		"You are inside a bedroom. A large bed is sited against the southern "+
		"wall, and on the eastern wall there is a table with a comfortable "+
		"looking chair infront. A small oil-lamp stands on the table, and light "+
		"up the room, not much, but appearantly enough. The window is above "+
		"the table, but it has been closed on the outside. @@exa_bed@@\n");
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
	ITEM(({"bedroom", "room"}), "It must be a bedroom, since there is a large "+
		"bed placed in here. It looks like there is room for two people there.\n");
	ITEM("bed", "@@exa_bed@@\n");
	ITEM("table", "The table looks old, and could be made out of oak, a common "+
		"tree around here. It has a large drawer which is @@exa_drawer@@. On top "+
		"of the table there stand an oil-lamp, lighting up the room, and some pens "+
		"and ink there is too.\n");
	ITEM("chair", "The chair looks real comfortable.\n");
	ITEM(({"oil-lamp", "lamp"}), "The oil-lamp is lit, and the owner of the house "+
		"has nailed it to the table. Maybe he is afraid of thieves?\n");
	add_exit(ARCHET_DIR +"inside", "north", 0);
	//man = clone_object(ER_DIR +"npc/timberman");
	//man->move(TO);
	//tell_room(QCTNAME(man)+" arrives from the hall.\n");
	//reset_room();
}

void
init()
{
	::init();
	add_action("do_open", "open");
	add_action("do_sit", "sit");
	add_action("do_lay", "lay");
}

int
do_sit(string str)
{
	if (!str)
	{
		NF("Sit where?\n");
		return 0;
	}
	
	if (str == "in chair" || str == "in the chair" || str == "in a chair")
	{
	write("You try to sit down in the chair.\n"+
		"Too late you discover that there is a HUUuuuuggeee nail stuck "+
		"in the chair....OUCH!!\n"+
		"That really hurt!\n");
	TP->command("scream");
	tell_room(QCTNAME(TP)+" Tries to sit down in the chair.\n"+
		"Too late "+HE_SHE(TP)+" discover that there is a huugeee nail stuck "+
		"in the chair......\n"+
		"THAT must really have hurt!\n", TP);
	return 1;
	}
}

int
do_lay(string str)
{
	if(!str)
	{
		NF("Lay where?\n");
		return 0;
	}
	if (str == "down in bed" || str == "down in the bed" || str == "in bed")
	{
		write("As you try to lay down in the bed you discover that it is filled with "+
		"dirt, filth, hair and everything you wish wasnt there!\n");
		tell_room(QCTNAME(TP)+" suddenly discovers filth, dirt, hair and other crap "+
		"spread around in the bed, as "+HE_SHE(TP)+" tries to lay down there!\n", TP);
		return 1;
	}
	else
	{
		write("Be more precice please!\n");
		return 0;
	}
}

int
do_open(string str)
{
	if (!strlen(str))
	{
		NF("Open the nothing?\n");
		return 0;
	}
	if (str != "drawer")
	{
		NF("Open the "+str+"?\n");
		return 0;
	}
	write("You try to open the drawers in the table, but they are stuck!\n");
	tell_room(QCTNAME(TP)+" tries to open the drawers in the table, but fails. "+
		"They are stuck like they are now.\n", TP);
	return 1;
}
/*
reset_room()
{
	if (!present(objectp(man)))
	{
		man = clone_object(BREE_DIR +"npc/timberman");
		man->move(TO);
		tell_room(QCTNAME(man)+" arrives from the hall.\n");
	}
}
*/
string
exa_drawer()
{
	/*if (drawer_state = OPEN)
		return "open";
	else*/
		return "closed";
}

string
exa_bed()
{
	/*if (present(man))
		return QCTNAME(man)+" is laying in the bed.\n";
	else*/
		return "The bed is empty.";
}

