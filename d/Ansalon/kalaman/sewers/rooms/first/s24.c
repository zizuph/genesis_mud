#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/sewers/local.h"

inherit SEWER_IN;

void
create_sewer_room()
{
    ::create_sewer_room();
    add_exit(FIRST + "s8", "north");
    add_exit(FIRST + "s31", "southwest");
    add_exit(FIRST + "s25", "southeast");
}
