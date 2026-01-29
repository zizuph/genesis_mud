#include "def.h"
inherit "/d/Rhovanion/daneel/lib/field";
#include "/sys/macros.h"

create_area()
{
	set_area_desc("western");
	set_area_type(12);
	set_area("river Celduin");
	set_land("Rhovanion"));
	set_area_name("outside Mirkwood");
	set_grass_type("light green grass");
	set_long("As you look around you see the Celduin to the east "
		+ "and Mirkwood to the south and west. The path continues "
		+ "north and south along Celduin.");
	add_exit(THIS_DIR+"w2","north",0);
	add_exit(THIS_DIR+"w4","south",0);
	make_the_room()
}
