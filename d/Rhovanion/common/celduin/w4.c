inherit "/d/Rhovanion/daneel/lib/field";
#include "def.h"
#include "/sys/macros.h"

create_room()
{
	set_area_desc("western");
	set_area_type(12);
	set_area("river Celduin");
	set_land("Rhovanion");
	set_area_name("Esgaroth");
	grass("dark green grass among the trees");
	extraline("you are standing just north of the marshes. "
	        + "Farther north you see the Long Lake, the path "
		+ "continues to the south and north along Celduin."

	add_exit(THIS_DIR+"w3","north",0,2);
	add_exit(THIS_DIR+"w5","south",0,2);
	make_the_room();
}
