inherit "/std/room";
#include "road.h"

create_room() {

	set_short("West end of Temple Road");
	set_long(BS("You are walking along the north wall of The Temple of Tyr "+
	"and a bit farther along the road you see the Gladiator arena, and a bit "+
	"to your northeast you see the slave pits. Farther east you can see a "+
		"golden tower. There is a town square to the west.\n",70));


   add_exit(SQUA_D+"square3","west");
   add_exit(TEM_STR+"road2","east");

	add_item(({"pit","pits","slave pits","slave pit"}),BSS(
		"The pits are where the rulers of Tyr keep their "+
		"prisoners before the time has come to sell them "+
		"on the slave market.\n"));

	add_item(({"tower","golden tower"}),BSS(
		"The Golden Tower is huge, and with your common knowledge "+
		"of Tyr, you know something about the treasures kept in "+
		"the tower, but you also know about the dangers in trying "+
		"to enter it, and of trying to steal from it.\n"));

	add_item(({"temple","wall"}), BSS(
		"From here you can only see the northern walls of the temple "+
		"and what you see is not much. You notice that the entrance is "+
		"not on this side.\n"));

	add_item(({"arena","gladiator arena"}),BSS(
		"A bit farther down the road, you see the public entrance to "+
		"the arena.\n"));

}
