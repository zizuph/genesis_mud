inherit "/d/Emerald/std/clone_handler";

#include "/d/Emerald/defs.h"

/* Called by /d/Emerald/telseron/rd31.c */

void
create_clone_handler()
{
	set_default_area("/d/Emerald/telseron/castle/");

	set_excluded_destinations( ({ TELSERON_DIR + "castle/ml",
		TELSERON_DIR + "castle/q_closet",
		TELSERON_DIR + "castle/q_room",
		TELSERON_DIR + "castle/q_chamber",
		TELSERON_DIR + "castle/q_dr"
		  }) );

	add_clone(TELSERON_DIR + "npc/wanderguard", 1, 10,
		 TELSERON_DIR + "castle/", 
		"An elf guard patrols the castle.\n");

	add_clone(TELSERON_DIR + "npc/elfguard", 2, 5,
		 TELSERON_DIR + "castle/out_court",
		 "An elf guard guards the court.\n");

	add_clone(TELSERON_DIR + "npc/elfguard", 3, 2,
		 TELSERON_DIR + "castle/q_ac",
		 "An elf guard guards the Queen.\n");

	add_clone(TELSERON_DIR + "npc/elfguard", 4, 2,
		 TELSERON_DIR + "castle/g_rm01",
		 "An elf guard guards the court.\n");

	add_clone(TELSERON_DIR + "npc/elfguard", 5, 2,
		 TELSERON_DIR + "castle/g_rm02",
		 "An elf guard guards the court.\n");

	add_clone(TELSERON_DIR + "npc/elfguard", 6, 2,
		 TELSERON_DIR + "castle/cor20",
		 "An elf guard guards the court.\n");

	add_clone(TELSERON_DIR + "npc/page", 7, 5,
		 TELSERON_DIR + "castle/",
		 "An young page scampers by.\n");

	add_clone(TELSERON_DIR + "npc/lady", 8, 5,
		 TELSERON_DIR + "castle/",
		 "An lady-in-waiting brushes by.\n");

	add_clone(TELSERON_DIR + "npc/servant", 9, 7,
		 TELSERON_DIR + "castle/",
		 "An servant scurries by.\n");

	set_clone_handler_id("Telseron Castle Clone Handler");
}
