#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;

void
reset_kalaman_room()
{
    return;
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Up on the battlements above the western gate of Kalaman");
    add_item_wall();
    add_item(({"nightlund","river","vingaard river",
	"plains","plains of solamnia","west"}),
      "@@west_wall");
    add_item(({"western gate","gate"}),
      "You stand above the western gate of Kalaman.\n");

    add_exit(WALL + "g6","northeast",0);
    add_exit(WALL + "g4","southwest",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand high up on the battlements on the wall " +
    "above the western gate of Kalaman. " +season_battlements()+
    west_desc();
}
