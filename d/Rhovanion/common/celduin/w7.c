inherit "/d/Rhovanion/daneel/lib/field";
#include "def.h"
#include "/sys/macros.h"

create_area()
{
	set_area_desc("western");
	set_area_type(12);
	set_area("river Celduin");
	set_land("Rhovanion");
	set_area_name("Mirkwood");
	set_grass_type("dark green grass among the trees");
	set_long("You can just see the path continuing to the "
	        + "northwest and to the south along Celduin. "

	add_exit(THIS_DIR+"w6","north",0,2);
	add_exit(THIS_DIR+"w8","south",0,2);
	make_the_room();
}
