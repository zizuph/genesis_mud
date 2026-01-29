inherit "/std/room";

#include "specials.h"

create_room()	{

	set_short("Outside the Main Gate of Tyr");
	set_long(BSS("You are standing outside the Main Gate "+
		"of Tyr, the city with its gate is to the east, "+
		"while to the southwest, the road makes its path "+
		"through the vast deserts of Athas.\n"));

	add_exit(SPEC_D+"maingate","east","@@pass_gate");
	add_exit(ROAD_D+"road5","southwest",0,3);

}

pass_gate()	{
	write(BSS("You hail the guards as you pass through the gates "+
		"glad to have escaped the vast desert.\n"));
}

