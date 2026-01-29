inherit "/d/Emerald/std/clone_handler";

#include "/d/Emerald/defs.h"

void
create_clone_handler()
{
	set_default_area("/d/Emerald/eclipsia/coral_requiem/");

	set_excluded_destinations( ({
		ECLIPSIA_DIR + "coral_requiem/s1",
		ECLIPSIA_DIR + "coral_requiem/cr6",
		ECLIPSIA_DIR + "coral_requiem/cr7",
		ECLIPSIA_DIR + "coral_requiem/cr8",
		ECLIPSIA_DIR + "coral_requiem/cr9",
		ECLIPSIA_DIR + "coral_requiem/cr10",
		ECLIPSIA_DIR + "coral_requiem/cr16",
		ECLIPSIA_DIR + "coral_requiem/cr17",
		ECLIPSIA_DIR + "coral_requiem/cr18",
		ECLIPSIA_DIR + "coral_requiem/cr19",
		ECLIPSIA_DIR + "coral_requiem/cr20",
		ECLIPSIA_DIR + "coral_requiem/store",
		ECLIPSIA_DIR + "coral_requiem/treasureroom"
		  }) );

	add_clone(ECLIPSIA_DIR + "npc/sing-mermaid",
		1, 3, ECLIPSIA_DIR + "coral_requiem/bwl",
		"Something sits up just inside of the shelter.\n");

	add_clone(ECLIPSIA_DIR + "npc/merpatrol", 2, 4,
		 ECLIPSIA_DIR + "coral_requiem/", 
		"A merman swims up to his post.\n");

        add_clone(ECLIPSIA_DIR + "npc/smallfish", 3, 20,
		ECLIPSIA_DIR + "coral_requiem/",
		"Some small fish swim around.\n");

        add_clone(ECLIPSIA_DIR + "npc/bigfish", 4, 6,
		ECLIPSIA_DIR + "coral_requiem/",
		"Some big fish swim around.\n");


        add_clone(ECLIPSIA_DIR + "npc/merman", 5, 3,
		ECLIPSIA_DIR + "coral_requiem/",
		"A merman swims up.\n");

        add_clone(ECLIPSIA_DIR + "npc/mermaid", 6, 3,
		ECLIPSIA_DIR + "coral_requiem/",
		"A mermaid swims up.\n");

        add_clone(ECLIPSIA_DIR + "npc/merchild", 7, 2,
		ECLIPSIA_DIR + "coral_requiem/",
		"A merchild swims up.\n");

        add_clone(ECLIPSIA_DIR + "npc/mako", 8, 1,
		ECLIPSIA_DIR + "coral_requiem/cr17",
		"A dangerous shark suddenly swims in.\n");

	set_clone_handler_id("Eclipsia Coral Requiem Clone Handler");
}
