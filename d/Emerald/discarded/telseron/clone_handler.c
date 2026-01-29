inherit "/d/Emerald/std/clone_handler";

#include "/d/Emerald/defs.h"

/* Called by /d/Emerald/telseron/nw_gate.c */

void
create_clone_handler()
{
	set_default_area("/d/Emerald/telseron/");

	set_excluded_destinations( ({
		TELSERON_DIR + "pub",
                TELSERON_DIR + "post",
		TELSERON_DIR + "post_foyer",
		TELSERON_DIR + "adv_guild",
		TELSERON_DIR + "com_room",
                TELSERON_DIR + "common_room",
		TELSERON_DIR + "armorer",
                TELSERON_DIR + "armory",
                TELSERON_DIR + "flower_store",
                TELSERON_DIR + "store",
                TELSERON_DIR + "forge",
                TELSERON_DIR + "housebase",
                TELSERON_DIR + "ic_shop",
                TELSERON_DIR + "inn",
                TELSERON_DIR + "road1_base",
                TELSERON_DIR + "streetbase",
                TELSERON_DIR + "township_base",
                TELSERON_DIR + "township_tell",
                TELSERON_DIR + "warehouse"
		  }) );

	add_clone(HOME_DIR + "npc/elf_patrol", 1, 2,
		 TELSERON_DIR + "garden/", 
		"An elf guard patrols the area.\n");

	add_clone(HOME_DIR + "npc/elf_patrol", 2, 7,
		 TELSERON_DIR, "An elf guard patrols the area.\n");

	add_clone(TELSERON_DIR + "npc/trader", 3, 10,
		 TELSERON_DIR, 
		"A merchant looks around for buyers.\n");

        add_clone(TELSERON_DIR + "npc/citizen", 4, 10,
		TELSERON_DIR,
		"The citizens of Telseron mill about.\n");

        add_clone(TELSERON_DIR + "npc/child", 5, 7,
		TELSERON_DIR,
		"Children run by you while giggling.\n");


        add_clone(TELSERON_DIR + "npc/kidleader", 6, 3,
		TELSERON_DIR,
		"A rough looking kid runs past you.\n");

        add_clone(TELSERON_DIR + "npc/traveller", 7, 5 + random(3),
		TELSERON_DIR,
		"A traveller trudges wearily in.\n");

	set_clone_handler_id("Telseron City Clone Handler");
}
