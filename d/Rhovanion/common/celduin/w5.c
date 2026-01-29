inherit "/d/Rhovanion/daneel/lib/field";
#include "def.h"
#include "/sys/macros.h"

create_area()
{
	set_area_desc("western");
	set_area_type(12);
	set_area("river Celduin");
	set_land("Mirkwood");
	set_area_name("Mirkwood");
	grass("dark green grass among the trees");
	extraline("you are standing outside Mirkwood. The "
	        + "path conitues north and southeast Celduin. ");

	add_exit(THIS_DIR+"w4","north",0,2);
	add_exit(THIS_DIR+"w6","southeast",0,2);
	make_the_room();
}
