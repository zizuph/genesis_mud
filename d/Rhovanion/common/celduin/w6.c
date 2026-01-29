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
	set_long("as you look around you see the Men-i-Naugrim "
		+ "just to the south of you, the path continues to "
		+ "the north.");
	add_exit(THIS_DIR+"w5","northwest",0,2);
	add_exit(THIS_DIR+"w7","south",0,2);
	make_the_room();
}
