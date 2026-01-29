inherit "/std/room";
#include "road.h"

create_room() {

	set_short("Southern end of Palace Road");
	set_long(BS("You are walking along on the Palace Road, and you notice that "+
	"the standard of the houses are improving as you walk farther north. "+
	"To the south you see the town square, and farther southeast you see a "+
	"large temple. Far north you notice a small castle, and the city "+
	"walls of Tyr.\n",70));


	add_exit(SQUA_D+"square3","south",0);
	add_exit(PAL_STR+"street2","north",0);

	add_item(({"small castle","castle"}), BSS(
		"The castle seems to be built in stone, close into the city "+
		"walls. You wonder a bit on who such a castle can be built for "+
		"when there is no sign of any sort on the walls. An unknown "+
		"castle!\n"));

	add_item(({"walls","city walls"}), BSS(
		"The walls look pretty impressive, maybe it is because "+
		"they built it to keep the enemies out?\n"));

	add_item(({"house","houses"}), BSS(
		"The houses have a good standard, just as you would "+
		"guess when you know that this part of Tyr only holds "+
		"the houses of nobles and templars.\n"));

	add_item(({"temple","large temple"}), BSS(
		"This is the Temple of Tyr, as you well know, and it's "+
		"pyramidic form is well known. There is an entrance "+
		"a bit south of here, just by the town square.\n"));

	add_item(({"square","town square"}), BSS(
		"This is the town square of Tyr, and if you are so interested "+
		"in knowing more about it, why don't you just go south and "+
		"look closer ?\n"));

	add_item(({"sand","desert sand"}), BSS(
		"This sand is definently sand that has blown in during "+
		"the permanent sand storms in the area.\n"));

}
