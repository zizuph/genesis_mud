/* Clone handler for the hallowed (orc) cavern.
   
   Code (c) 2000 to Damian Horton, BKA Casimir.
*/

inherit "/d/Emerald/std/clone_handler";

#include "/d/Emerald/defs.h"
#include "/d/Emerald/sys/paths.h"

#define ORC_DIR BLACKWALL_DIR + "orcs/"

void
create_clone_handler()
{
    set_default_area(ORC_DIR);
    // NPCs:

    add_clone(ORC_DIR + "npc/small_orc", 1, 9);
    add_clone(ORC_DIR + "npc/large_orc", 2, 9);
    add_clone(ORC_DIR + "npc/captain", 3, 1, ORC_DIR + "cave2");
    add_clone(ORC_DIR + "npc/lt1", 4, 1, ORC_DIR + "cave2");
    add_clone(ORC_DIR + "npc/lt2", 5, 1, ORC_DIR + "cave2");
}
   
    








