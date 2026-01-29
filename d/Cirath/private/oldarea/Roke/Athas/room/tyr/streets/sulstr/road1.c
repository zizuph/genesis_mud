inherit "/std/room";

#include "road.h"


create_room()	{
	set_short("Sul street");
	set_long(BSS("You have entered Sul street in the western parts of Tyr, "+
		"just southeast of the Main Gate. There is an inn to "+
		"west, whilst the road continues to the southeast. "+
		"You see some houses to the east and southeast of "+
		"here of fairly good standards.\n"));

	add_exit(SPEC_D+"maingate","northwest",0);
	add_exit(INNS_D+"inn1","west",0);
	add_exit(SUL_STR+"road2","southeast",0);

}
