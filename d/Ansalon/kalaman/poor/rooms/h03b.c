#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit HOUSE_STD;

void
reset_kalaman_room()
{
    return;
}

create_kalaman_room()
{
    set_short(query_house_short(HOUSE_LIVING));
    set_long(query_house_long(HOUSE_LIVING) + "\n");

    add_exit("h03a.c", "hallway");
    reset_kalaman_room();
}
