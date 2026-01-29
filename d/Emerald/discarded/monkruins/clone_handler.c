inherit "/d/Emerald/std/clone_handler";

#include "/d/Emerald/defs.h"

/* Called by /d/Emerald/telseron/nw_gate.c */

void
create_clone_handler()
{
	set_default_area("/d/Emerald/kroad/monkRUIN/");

        add_clone(MONKRUIN_DIR + "npc/undmonk1", 1, 10,
		  ( ({ MONKRUIN_DIR }) ), "An undead monk shuffles in.\n");

        add_clone(MONKRUIN_DIR + "npc/undmonk2", 2, 6,
		( ({ MONKRUIN_DIR }) ), "An undead monk shuffles in.\n");

	set_clone_handler_id("Emerald MonkRUIN Clone Handler");
}
