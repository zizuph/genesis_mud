inherit "/d/Rhovanion/lib/field";
#include "/sys/macros.h"
#include "def.h"

create_area()
{
	set_area_desc("western");
	set_area_type(12);
	set_area("river Celduin");
	set_land("Rhovanion");
	set_area_name("Esgaroth");
	set_grass_type("dark green grass.");
	set_long("you are standing just south of the Long Marshes "
	  + "where the Forest River runs into Long Lake. the path "
	  + "continues northeast towards Esgaroth and to the south "
	  + "along Long lake, and you see another path following the "
	  + "Forest River to the west.");
	add_exit("/d/Rhovanion/common/esgarroth/entr","northeast",0,1);
	add_exit(THIS_DIR+"w2","south",0,2);
	add_exit("/d/Rhovanion/common/mirkwood/thranduil/p10","west",0,2);
}
