// file name: d/Avenir/common/outpost/bridge.c
// creator(s):  Kazz    March '95
// last update:
// purpose:     Spans the chasm
// note:	
// bug(s):
// to-do:	
//

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/common/outpost/cave.h"

inherit "/std/room";

create_room()
{
	SHORT("Bridge over chasm");
	LONG( "You stand on a small stone bridge above the horrific chasm. "+
	      "Foul, musty, warm wind blows up from below. North leads "+
	      "toward flames of fire and the black fort. South leads across "+
	      "the chasm, deeper into the stygian darkness.\n" );
	
	add_exit(OUTPOST + "cave3","north",0);
	add_exit(OUTPOST + "chasm_south","south",0);

	FLAME

        add_item(({"fort"}),
		 "The fort is black and lies against the cavern wall, it's "+
		 "tall tower brushes the sloping cavern wall.\n" );
        add_item(({"chasm"}),
		 "The chasm is at least fifty feet wide. The bottom "+
		 "is cloaked in darkness.\n");
	add_item(({"bridge"}),
		 "The bridge seems newly constructed of tunnel rock. It is "+
		 "rather small and perhaps not too sturdy. Stones settle "+
		 "beneath your feet.\n" );
	add_item(({"wind"}),
		 "The foul wind fills your nose with death.\n" );
	add_item(({"cavern", "cavern wall"}),
		 "The cavern wall slopes down toward the fort.\n" );

	LIGHT						  
	IN

} // create_room()


