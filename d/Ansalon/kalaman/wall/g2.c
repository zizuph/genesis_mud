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
    set_short("Up on the battlements above the harbour gate");
    add_item_wall();
    add_item(({"east","harbour","harbour district"}),
      "@@east_wall");
    add_item(({"gate","harbour gate"}),
      "Beneath you is the harbour gate of Kalaman.\n");

    add_exit(WALL + "g1","northwest",0);
    add_exit(WALL + "g3","southeast",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand high up on the battlements on the wall " +
    "overlooking the harbour gate. " +season_battlements()+
    east_desc();
}
