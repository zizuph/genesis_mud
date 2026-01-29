inherit "/std/room";

#include "/d/Roke/common/defs.h"

create_room()	{

	set_short("Main Gate of Tyr");
	set_long(BSS("You are standing just inside the Main Gate of Tyr, the "+
		"Main Gate Road is leading east from here, towards "+
		"the town square, and Sul Street is making its path "+
		"southeastwards. To the north you see the beginning "+
		"of Dragon Street in the western part of the nobles "+
		"areas.\n"));

	add_exit(/*DRA_STR+*/"xxx","north","@@closed");
	add_exit(MGR_STR+"road7","east" );
	add_exit(SUL_STR+"road1","southeast" );
	add_exit(SPEC_D+"maingate2","west","@@pass_gate");

}

pass_gate()	{
	write(BSS("You hail the guards as you walk through the gates "+
		"on your way towards the vast deserts of Athas.\n"));
}

closed()	{
	write(BSS("Due to intense building activities in this area, "+
		"Dragon road in the nobles area is closed. We hope "+
		"to be finished with it as soon as possible.\n"));
	return 1;
}
