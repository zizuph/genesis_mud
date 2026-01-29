#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>

inherit TBROADROOM;

void
create_tbroad_room()
{
    set_short("a road in the Taman Busuk mountains");

    set_mountain();
    add_prop(ROOM_I_TERRAIN_TYPE,
	TERRAIN_MOUNTAIN);

    add_mountain_items();

}
