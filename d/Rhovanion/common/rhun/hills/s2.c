
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Under the pier");
    set_long("You stand beneath an old, wooden pier on the east "+
	"side of a large town which lies at the northwest end of "+
	"the Sea of Rhun.  You can hear a few people pass overhead, "+
	"but there is no way to climb up to the pier from here.  Your "+
	"only option is to continue along the beach, either north "+
	"or south.\n");
	
    AE(RHUN+"hills/s1", "north");
    AE(RHUN+"hills/s3", "south");
    
    add_item(({"beach","sand"}), 
        "The sandy beach leads away from here "+
	"to the north and south.\n");
    add_item("pier", "The old pier is made of wood, and passes "+
	"just over your head.  There is no way to reach it from "+
	"here.\n");    
}
