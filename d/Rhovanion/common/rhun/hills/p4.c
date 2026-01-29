
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Mountain path");
    set_long("The mountain path continues on its way, making "+
	"its narrow way along the mountain's edge.  From here "+
	"it makes a sharp turn, heading from northwest to "+
	"northeast.\n");
	
    AE(RHUN+"hills/p3", "northeast");
    AE(RHUN+"hills/p5", "northwest");
    
    add_item("path", "The path heads off to the northeast and "+
	"northwest from here, winding its way along the cliff's "+
	"edge.\n");
    add_item(({"mountain", "peak", "up"}), "The moutain peak "+
	"along whose edge you follow is quite tall and forbidding, "+
	"rising up far above your head.\n");
}
