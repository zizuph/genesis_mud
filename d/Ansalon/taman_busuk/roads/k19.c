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
    set_short("the foothills of the Taman Busuk mountains");
    set_extra_long("These are the foothills of the " +
	"Taman Busuk mountains. The mountain range is to the south, " +
	"with the beginning of a road leading east along the mountainside. " +
	"To the north the plains of Estwilde stretch as " +
	"far as you can see.");

    // add_exit(TBROADS + "k19", "northwest");
    add_exit(TBROADS + "k18", "east",0,"@@road_tired");
    set_mountain();
    add_prop(ROOM_I_TERRAIN_TYPE,
	TERRAIN_HILL | TERRAIN_ROAD);

    add_mountain_items();
    add_road_items();

}
