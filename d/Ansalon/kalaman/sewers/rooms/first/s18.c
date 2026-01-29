#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/sewers/local.h"

inherit SEWER_IN;

void
create_sewer_room()
{
    ::create_sewer_room();
    add_exit(FIRST + "s22", "south");
    add_exit(FIRST + "s17", "southeast");
    add_exit(FIRST + "s19", "north");
    add_exit(FIRST + "s20", "southwest");
}
