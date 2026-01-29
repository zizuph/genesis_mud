inherit "/d/Emerald/std/clone_handler";

#include "/d/Emerald/defs.h"

void
create_clone_handler()
{
  	set_excluded_destinations ( ({
	LEAH_DIR + "house2-bedroom",
	LEAH_DIR + "house2-main",
	LEAH_DIR + "house2-kitchen",
	LEAH_DIR + "house2-bushes" }) );
  
	set_default_area("/d/Emerald/leah/");

        add_clone(LEAH_DIR  + "npc/child", 1, 5,
		  (({ LEAH_DIR}) ), "An elf child plays around you.\n");


        add_clone(LEAH_DIR + "npc/citizen", 2, 4,
		( ({ LEAH_DIR }) ), "An elf citizen walks through Leah.\n");

	set_clone_handler_id("Emerald Leah Clone Handler");
}
