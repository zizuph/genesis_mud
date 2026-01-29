// file name: d/Avenir/common/outpost/cave1.c
// creator(s):  Kazz    Jan '95
// last update: Lilith Apr 2022: Fort makeover
// purpose:     near tunnel of the outpost cave.
// note:
// bug(s):


#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/common/outpost/cave.h"

inherit "/d/Avenir/inherit/room";

void
create_domain_room()
{
	set_short("inside an ancient magma tube");
	set_long("This is a massive magma tube formed by volcanic "+
        "activity thousands of years ago. "+
        "To the southeast is a tall, black fort wedged into an "+
        "opening in the wall, blocking passage into a cavern "+
        "from which a powerful light emits. "+
        "Two huge flames burn on either side of the path "+
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


