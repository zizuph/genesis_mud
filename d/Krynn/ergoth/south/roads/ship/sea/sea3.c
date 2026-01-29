#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>

inherit OR_FILE

void create_krynn_room()
{
    set_short("At sea");
    set_long("At sea in the Straights of Algoni\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
