inherit "/d/Emerald/std/clone_handler";

#include "/d/Emerald/defs.h"

void
create_clone_handler()
{
	set_default_area("/d/Emerald/telseron/garden/");

	add_clone(HOME_DIR + "npc/elf_patrol", 1, 2,
		 TELSERON_DIR + "garden/", 
		"An elf guard patrols the area.\n");

        add_clone(TELSERON_DIR + "npc/citizen", 2, 3,
		TELSERON_DIR + "garden/",
		"The citizens of Telseron mill about.\n");

        add_clone(TELSERON_DIR + "npc/child", 3, 2,
		TELSERON_DIR + "garden/",
		"Children run by you while giggling.\n");

	set_clone_handler_id("Telseron Garden Clone Handler");
}
