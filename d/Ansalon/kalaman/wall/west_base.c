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
    set_short("Up on the battlements on the wall surrounding Kalaman");
    add_item_wall();
    add_item(({"nightlund","river","vingaard river",
	"plains","plains of solamnia","west"}),
      "@@west_wall");

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand high up on the battlements on the wall " +
    "surrounding Kalaman. " + season_battlements() +
    west_desc();
}
