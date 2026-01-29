#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/sewers/local.h"

inherit DWARF_TUNNEL;

void
create_sewer_room()
{
    ::create_sewer_room();
    add_exit(SECOND + "s10", "southwest");
    add_exit(SECOND + "s8", "north");
    add_exit(FIRST + "middle", "up");
}
