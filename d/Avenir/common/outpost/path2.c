// file name: d/Avenir/common/outpost/path2.c
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
	SHORT("Dark, damp tunnel");
	LONG( "This dark, quiet, tunnel leads northwest and upwards " +
	      "toward a damp " +
	      "breeze, and to the southeast is more darkness.\n" );

	add_exit(OUTPOST + "path1","northwest",0);
	add_exit(OUTPOST + "path3","southeast",0);

	add_item(({"wind", "breeze", "damp wind"}),
		 "A damp, cool breeze wafts down from the northwest. " +
		 "It seems to be stronger from that direction.\n" );
	ADD_TUNNEL_ITEMS
	
	IN

} // create_room()

