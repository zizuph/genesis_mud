// file name: d/Avenir/common/outpost/cave1.c
// creator(s):  Kazz    Jan '95
// last update:
// purpose:     near tunnel of the outpost cave.
// note:
// bug(s):
// to-do:  turn the knock add_cmd_item into a function to actually allow
//	    players inside.

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/common/outpost/cave.h"

inherit "/std/room";

create_room()
{
	SHORT("Inside an immense cavern");
	LONG( "You stand within an immense cavern. To the southeast is a "+
	      "tall, black fort wedged against the wall of the cavern. "+
	      "A lone tower juts up, reaching toward the curving "+
	      "wall above. Two huge flames burn on either side of the path "+
	      "leading to the stone gates. Further to the south, an "+
	      "immense chasm slices through the floor.\n" );

	add_exit(OUTPOST + "cave2","southeast",0);
	add_exit(OUTPOST + "path4","northwest",0);

	CAVERN
	FORT
	TOWER
	WALL
	FLAME
	PATH
	GATE
	FLOOR
	CHASM
	ROCKS
	
	LIGHT
	IN

} // create_room()


