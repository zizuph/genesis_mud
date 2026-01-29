/*
 * Guestroom in Elrond's House
 * By Finwe, December 1997
 */
 
#pragma strict_types
 
#include "../local.h"
#include "/d/Shire/rivendell/room/valley/forge/forge.h"
 
inherit HOUSE_IN_BASE;
 
void
create_house_room()

{
    set_short("A large chamber");

    set_long("This is a comfortable sized hall. It isn't lavish " +
        "but rather peaceful and tidy. To the west is an arch " +
        "leading to a forge. Another arch in the north wall " +
        "leads north is a shop of some sort. A large window " +
        "is set into the south wall and a rug covers the floor.\n");
     
    add_item("rug",
        "The rug is thick and luxurious. It is a maroon color " +
        "with a golden fringe. The rug is decorated with a " +
        "large anvil and hammer.\n");
    add_item(({"fringe", "golden fringe"}),
        "The fringe is made from golden colored strands of yarn " +
        "and are about a hand's length long.\n");

    set_extra_window("@@window_position@@ set into the " +
        "south wall.");
    add_item(({"south window", "southern window"}),
        "@@south_down@@ The stable is visible from here.\n");
 
    num_of_windows=1;
    set_extra_floor("A beautiful rug covers the floor.");
 
    add_exit(FORGE_DIR +  "new_forge", "west");
    add_exit(VALLEY_DIR + "n_path03", "out");
}
