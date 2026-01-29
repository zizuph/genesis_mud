inherit "/std/room";

#include "road.h"

create_room()	{
	set_short("Palace Roads");
	set_long(BSS("You are walking along the Temple Road, and "+
		"directly north of here you see the slave pits, "+
		"and you are glad you are not one of the slaves in "+
		"it. The road goes east and west, and you can enter "+
		"the slave pit to the north. South of you, you can see "+
		"walls to the Gladiatorial stadium, and to the "+
		"southwest you can see the Temple of Tyr.\n"));

   add_exit(TEM_STR+"road2","west");
	add_exit(TEM_STR+"road4","east",0);
	add_exit(SQUA_D+"slavepit","north","@@noticed");

}

noticed()	{
	write(BSS("You notice that the guard examines you carefully "+
		"when you enter, and you feel releaved, since he then "+
		"might remember that you are not a slave.\n"));
}

