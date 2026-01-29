inherit "/d/Rhovanion/daneel/lib/field";
#include "def.h"
#include "/sys/macros.h"

create_area()
{
	set_area_desc("western");
	set_area_type(12);
	set_land("Rhovanion");
	set_area("river Celduin");
	set_area_name("Esgaroth");
	set_grass_type("dark green grass among the trees");
        set_long("you are standing where Long Lake runs out "
	        + "into River Celduin, which, you have heard,  "
		+ "continues southeast till it meets Sea of Rhun. "
		+ "The path runs northwest along Long Lake to the "
		+ "Long Marshes, and south along Celduin.");

	add_exit(THIS_DIR+"w1","north",0,2);
	add_exit(THIS_DIR+"w3","south",0,2);
	make_the_room();
}
