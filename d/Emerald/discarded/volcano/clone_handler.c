inherit "/d/Emerald/std/clone_handler";
#include "/d/Emerald/mountains/volcano/vol.h"

void
create_clone_handler()
{
	set_default_area("/d/Emerald/mountains/volcano/");

add_clone(VNPC + "wom4.c", 1, 1, VOL + "top.c", "A native woman enters the room.\n");
add_clone(VNPC + "herbwom.c", 2, 1, VOL + "hrbtent.c", "The herbalist enters from the storeroom.\n");
add_clone(VNPC + "postwom.c", 3, 1, VOL + "mtent.c", "The shop keeper enters from upstairs.\n");

add_clone(VNPC + "man1.c", 4, 6, VOL, "A native enters the room.\n");
add_clone(VNPC + "man2.c", 5, 6, VOL, "A native enters the room.\n");
add_clone(VNPC + "man3.c", 6, 6, VOL, "A native enters the room.\n");
add_clone(VNPC + "man4.c", 7, 6, VOL, "A native enters the room.\n");

add_clone(VNPC + "wom1.c", 8, 6, VOL, "A native woman enters the room.\n");

add_clone(VNPC + "boy1.c", 9, 4, VOL, "A young boy runs into the room.\n");
	set_clone_handler_id("Emerald Volcano Clone Handler");
}
