inherit "/std/room";

#include "specials.h"

create_room()	{

	set_short("Stadium Gate in Tyr");
	set_long(BSS("You are standing at the inside of the Stadium Gate, "+
		"just southeast of Sul street. The gates are not so big "+
    "as the Main Gates, but they still look pretty "+
		"impressive.\n"));

	add_exit(SUL_STR+"road8","northwest" );
	add_exit(SPEC_D+"stadgate2","south","@@pass_gate");

}

pass_gate()	{
	write(BSS("You hail the guards as you walk through the gates "+
		"on your way towards the wast deserts of Athas.\n"));
	return 0;
}
