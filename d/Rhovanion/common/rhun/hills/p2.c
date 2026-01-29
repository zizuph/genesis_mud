
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Mountain path");
    set_long("You follow this very-narrow path as it curves "+
	"along, here leading from west to northeast.  High "+
	"above you, brewing clouds signal the approach of "+
	"a storm.  There is also a cave with a rather "+
	"large entrance standing just southwest of here.\n");
	
    AE(RHUN+"hills/p1", "northeast");
    AE(RHUN+"hills/p3", "west");
    AE(RHUN+"hills/cave", "southwest");
    
    add_item("path", "The path heads off to the northeast and "+
	"west from here, winding its way along the cliff's "+
	"edge.\n");
    add_item(({"mountain", "peak", "up"}), "The moutain peak "+
	"along whose edge you follow is quite tall and forbidding, "+
	"rising up far above your head.\n");
    add_item(({"sky", "overhead", "clouds", "storm"}), "Dark clouds "+
	"hang overhead, predicting the onslaught of a storm.\n");
    add_item("cave", "The cave looks to be the home of some "+
	"large creature.  It would be quite easy to enter.\n");
}
