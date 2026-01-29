inherit "/std/room";

#include "road.h"

create_room()	{
	set_short("Warrior's Way");
	set_long(BSS("This is the south end of Warriors Way, which leads "+
		"between the Gladiator Stadium and Sul Street, just "+
		"by the stadium gate. The Kings Garden is east of you, "+
		"and the entrance to the Gladiator Guild is to the "+
		"west. Further north you can see the arena, and to "+
		"the southeast you see the Stadium Gate.\n"));

	add_item(({"garden","kings garden"}), BSS(
		"The garden is green and bloomy, and you start to "+
		"wonder how the king can keep it in such a good "+
		"shape, here in the middle of the desert.\n"));

	add_item(({"gate","stadium gate"}), BSS(
		"The gate is lightly smaller than the Main Gate, and "+
		"much smaller than the Grand Gate. It leads south, "+
		"into the the great desert of Athas.\n"));

	add_item(({"stadium","arena"}), BSS(
		"The stadium looks mighty impressive from here, and "+
		"you notice a sign on the wall from here.\n"));

	add_item(({"sign",}), BSS(
		"The sign is huge, but still to far away for "+
		"you to read it from here.\n"));


   add_exit(GLAD_DIR+"entrance","west");
   add_exit(WAR_STR+"road1","north");
   add_exit(SUL_STR+"road8","south");

}

