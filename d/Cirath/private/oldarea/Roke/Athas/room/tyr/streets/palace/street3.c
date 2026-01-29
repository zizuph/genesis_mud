inherit "/std/room";
#include "road.h"
	object monster;

create_room() {

	set_short("On Palace Road");
	set_long(BSS("You are walking along on the Palace Road, leading "+
		"north from the town square. From here you can see the front "+
		"door of the templar Pandora's house, and the entrance through "+
		"the garden is east. On your west side you see the east wall of "+
		"the noble's banquet hall. You notice a small castle to the "+
		"north.\n"));

	add_item(({"small garden","garden"}),BSS(
		"It is a nice looking garden, maybe you should enter and "+
		"look closer ?\n"));

	add_item(({"large house","house"}),BSS(
		"You recognize this house to be the house of the "+
		"Templar Pandora, whom you have heard some roumors "+
		"about, but you didn't think it would be this impressive "+
		"even when you stand outside it's garden.\n"));

	add_item(({"hall","banquet hall"}),BSS(
		"You can only see the outside walls from here, but "+
		"even those are rather impressive.\n"));

	add_item(({"wall","walls"}),BSS(
		"The walls are quite impressive here, where they stand "+
		"high up, and you wonder what the inside of this "+
		"large hall could look like.\n"));

	add_item(({"door","front door"}), BSS(
		"You are too far away to notice anything special about the "+
		"door, but even from here you notice that it is closed.\n"));

	add_exit(SOR_DIR+"garden","east",0);
	add_exit(PAL_STR+"street2","south",0);
	add_exit(DIA_STR+"road1","north",0);

}
