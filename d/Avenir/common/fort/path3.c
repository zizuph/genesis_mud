// file name: d/Avenir/common/outpost/path3.c
// creator(s):  Kazz    Jan '95
// last update:
// purpose:     part of the tunnel between pier and outpost
// note:
// bug(s):
// to-do:  

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/outpost.h"

inherit "/std/room";

create_room()
{
        SHORT("A dark tunnel");
	LONG( "This dark, quiet, tunnel leads upslope to the northwest, and into darkness to the southeast.\n" );

	add_exit(OUTPOST + "path2","northwest",0);
	add_exit(OUTPOST + "path4","southeast",0);

	ADD_TUNNEL_ITEMS
	
	IN

} // create_room()

