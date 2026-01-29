inherit "/d/Emerald/std/clone_handler";

#include "/d/Emerald/defs.h"

/* Called by /d/Emerald/telseron/nw_gate.c */

void
create_clone_handler()
{
	set_default_area("/d/Emerald/kroad/");

	set_excluded_destinations( ({
		KROAD_DIR + "fallroom", KROAD_DIR + "fbaseroad",
		  KROAD_DIR + "water1" }) );
		

        add_clone(HOME_DIR + "npc/elf_patrol", 1, 15,
		  ( ROAD_ROOMS ), "An elf watches the road.\n");

        add_clone(HOME_DIR + "npc/elf_traveller", 3, 27,
		( ROAD_ROOMS ), "An elf arrives along the road.\n");

        add_clone(HOME_DIR + "npc/human_traveller", 4, 10,
		( ROAD_ROOMS ), "A human arrives along the road.\n");

        add_clone(HOME_DIR + "npc/gnome_traveller", 5, 2,
		( ROAD_ROOMS ), "A gnome arrives along the road.\n");

        add_clone(HOME_DIR + "npc/dwarf_traveller", 6, 3,
		( ROAD_ROOMS ), "A dwarf arrives along the road.\n");

	set_clone_handler_id("Emerald Kroad Clone Handler");
}
