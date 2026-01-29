inherit "/std/room";

#include "road.h"

create_room()	{
	set_short("Sul street");
	set_long(BSS("This is the eastern end of Sul Street, just by the "+
		"Stadium Gate. The Warriors Way leads north from "+
		"here, towards the Gladiatorial Arena, and west you "+
		"follow Sul Street towards the market and the Main "+
		"Gate of Tyr. You see a small path leading into the "+
         "King's Garden to the east, and southeast you see the "+
		"Stadium Gate.\n"));

	add_exit(SUL_STR+"road7","west",0);
	add_exit(WAR_STR+"road2","north",0);
	add_exit(PATH_STR+"path1","east","@@enter_path");
	add_exit(SPEC_D+"stadgate","southeast",0);

}

enter_path()	{
   write("You are not allowed to enter the King's Garden, "+
         "it might get you killed.\n");
	return 1;
}

