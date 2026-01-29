inherit "/std/room";

#include "/d/Roke/common/defs.h"

create_room()	{
	set_short("The Elfstone Tavern and Inn");
	set_long(BSS("You have entered the Elfstone Tavern and Inn, "+
		"one of the most expensive inns and taverns in all "+
		"of Athas. South of here you see the bar, and to the "+
		"west you see the reception. You can see some paintings "+
		"on the wall, and just over the exit to the street, "+
		"east, you see the family shield.\n"));

	add_item(({"shield","family shield"}), BSS(
		"The shield is small, not really a shield meant for "+
		"use in combat, more as a display. It is picturing "+
		"a group of elves, running through the waste lands "+
		"of Athas.\n"));

	add_item(({"picture","pictures","painting","paintings"}),BSS(
		"There are two paintings here, covering the north "+
		"wall. If you want to look closer at them, you will "+
		"have to name the one you want to look at. You "+
		"recognize them as 'Desert Dunes' and 'Elven Tribes'.\n"));

	add_item(({"Desert Dunes","desert dunes"}), break_string(
		"This is a truely magnificant picture, and you can almost "+
		"feel like you can enter it. The painting illustrates a "+
		"large part of the desert, and the dunes. On one of the closest "+
		"dunes you can see some footprints, and a small lizard is "+
		"crawling over another dune. There is a small gold plaque "+
		"at the bottom of the frame saying 'Desert Dunes by Ossacip "+
		"the Athasian'.\n",70));

	add_item(({"Elven Tribes","elven tribes"}), break_string(
		"This painting illustrates a small desert village built around "+
		"a small pond of water. The inhabitants are all elves, and "+
		"they are doing like they always do: the women bake, make "+
		"pots and wash clothes, while the men are running out "+
		"of the city to go hunting, or maybe travelling to Tyr to trade."+
		"On the bottom of the frame you see a small plaque saying "+
		"'Elven Tribes by Ossacip the Athasian'.\n",70));


	add_exit(INNS_D+"inn1a","west",0);
	add_exit(INNS_D+"inn1b","south","@@close");
	add_exit(SUL_STR+"road1","east",0);

}

close()	{
	write("The bar is closed this early in the day, please come back "+
		"later.\n");
	return 1;
}

