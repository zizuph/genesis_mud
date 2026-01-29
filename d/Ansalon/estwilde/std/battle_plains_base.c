#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit PLAINS_OUT;
inherit CONQUER_BASE

/*
* This function is called from the main Krynn room.
*/
nomask public void
create_krynn_room()
{
    ::create_krynn_room();
    set_area_name(AREA_NAME);
}

/*
* This function is called from the main Krynn room.
*/
nomask public void
reset_krynn_room()
{
    reset_conquer_room();
    ::reset_krynn_room();
}

void
init()
{
    init_conquer();
    ::init();
}

