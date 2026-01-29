inherit "/std/room";

#include "road.h"

create_room()	{

	set_short("Main Gate Road");
	set_long(BSS("You are walking on the Main Gate Road in Tyr, which "+
		"runs between the Main Gate and the town square and "+
		"the Temple of Tyr. You notice a post office to the "+
		"northwest, and a street leading south farther east. "+
		"There is a nice house stright to the north.\n"));

	add_item(({"house","nice house"}), BSS(
		"The house is large and typical for the noble "+
		"families.\n"));

	add_exit(MGR_STR+"road6","west",0);
	add_exit(NOBL_D+"min_ent","north","@@closed");
	add_exit(MGR_STR+"road4","east",0);

}

closed()	{
	write(BSS("A litte gnome pops up in the doorway, pushing "+
		"you back, saying: Sorry, but no one is let into "+
		"the Minthor family's house while they are on "+
		"vacation!\n"));
	return 1;
}

