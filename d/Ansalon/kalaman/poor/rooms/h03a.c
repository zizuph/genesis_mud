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
    set_short(query_house_short(HOUSE_HALLWAY));
    set_long(query_house_long(HOUSE_HALLWAY) + "\n");

    add_exit("h03c.c", "kitchen");
    add_exit("h03b.c", "living");
    add_exit("s03.c", "street");
    reset_kalaman_room();
}
