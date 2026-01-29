inherit "/d/Rhovanion/daneel/lib/field";
#include "/sys/macros.h"

create_area()
{
	set_area_desc("western");
	set_area_type(12);
	set_area("Celduin");
	set_area_name("Mirkwood");
	set_land("Rhovanion");
	set_grass_type("dark green grass among the trees");
	set_long("as you look around you see the Men-i-Naugrim "
		+ "just to the south of you, the path continues to "
		+ "the north.");
	add_exit(THIS_DIR + "e7","north",0,2);
	add_exit("/d/Rhovanion/common/mirkwood/oldforestroad/ofr20","south",0,2);
	make_the_room();
}
