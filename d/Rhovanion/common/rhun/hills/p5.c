
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Mountain path");
    set_long("You follow a narrow, winding path along the "+
	"windswept edge of a mountain peak.  It rises, towering "+
	"and dark, above your head for many hundreds of meters.  "+
	"A storm seems to be brewing overhead, and the occassional "+
	"crash of thunder startles you slightly.\n");
	
    AE(RHUN+"hills/p6", "north");
    AE(RHUN+"hills/p4", "southeast");
    
    add_item("path", "The path heads off to the north and "+
	"southeast from here, winding its way along the cliff's "+
	"edge.\n");
    add_item(({"mountain", "peak", "up"}), "The moutain peak "+
	"along whose edge you follow is quite tall and forbidding, "+
	"rising up far above your head.\n");
}
