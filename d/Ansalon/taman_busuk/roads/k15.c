#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>

inherit TBROADROOM;

void
reset_tbroad_room()
{
}

void
create_tbroad_room()
{
    set_short("a road in the Taman Busuk mountains");
    set_extra_long("This is a road among the " +
	"Taman Busuk mountains, twisting among " +
    "the peaks. The road leads north and southeast.");

    add_exit(TBROADS + "k16", "north",0,"@@road_tired");
    add_exit(TBROADS + "k14", "southeast",0,"@@road_tired");
    set_mountain();
    add_prop(ROOM_I_TERRAIN_TYPE,
	TERRAIN_MOUNTAIN | TERRAIN_ROAD);

    add_mountain_items();
    add_road_items();

}
