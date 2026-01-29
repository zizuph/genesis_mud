/* rd_tr_03: Middle section of Templar Road, 11/22/95. */
 
#pragma strict_types
 
inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/std/block.h"
 
void
create_room()
{
    set_short("templar Road center");
    set_long("Sandwiched between the gate into the slave pits to the "
            +"north and the northern wall of the brickyards to the "
            +"south, it is impossible here to shut out the screams and "
            +"moans of Tyr's tortured labor force. To make matters "
        +"worse, an awful smell of unwashed flesh, blood, and "
            +"refuse drifts out of the pits. Tarek guards on either "
            +"side of the gate gaze down coldly.\n");
 
    add_item(({"pits", "slave pits", "pit", "slave pit"}),
             "You can only listen to the cries, not see inside.\n");
    add_item(({"guards", "tarek", "guard", "tarek guards", "gate"}), 
             "Hairless and built like a six foot tall dwarf, the big "
            +"boned tarek makes a superb guard or pit fighter, "
            +"depending on its luck and intelligence.\n");
    add_cmd_item(({"moans", "to moans", "screams", "to screams"}),
             "listen", "You hear the "
            +"cries of the doomed, begging for freedom.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM
 
    add_exit(TYR_PITS+"gate.c", "north", "@@block_exit@@", 1); 
    add_exit(TYR_SLAVE+"rd_tr_04.c", "east", 0, 1);
    add_exit(TYR_SLAVE+"rd_tr_02.c", "west", 0, 1);
}
