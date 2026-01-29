inherit "/std/door";
#include "defs.h"

object
create_door()
{

    set_door_id("_castle_");
    sst_pass_command(({"e", "south"}));
    set_door_name(({"wooden door","door"}));
    add_item(({"wooden door", "door"}),
        "This is a magnificent mahoney wooden door. Intricate "+
        "carvings cover it from top to bottom, showing elves "+
        "doing different activities like hunting and falconery. "+
        "It seems surprising that this door has maintained its "+
        "sumptuous carvings compare with the rest of the portico.\n");
    set_open(2);
    set_other_room(OV_DIR + "castle/lcastle01");
}
