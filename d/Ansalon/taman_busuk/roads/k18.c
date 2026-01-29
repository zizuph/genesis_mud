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
    "the peaks to the south. " +
    "To the north the mountain range gives way to " +
    "an open plain. The road leads southeast " +
    "to the mountains, and west down the side of " +
    "the mountain onto the plains.");

    add_exit(TBROADS + "k19", "west",0,"@@road_tired");
    add_exit(TBROADS + "k17", "southeast",0,"@@road_tired");
    set_mountain();
    add_prop(ROOM_I_TERRAIN_TYPE,
	TERRAIN_MOUNTAIN | TERRAIN_ROAD);

    add_mountain_items();
    add_road_items();

}
