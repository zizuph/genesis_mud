#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/sewers/local.h"

inherit DWARF_TUNNEL;

void
create_sewer_room()
{
    ::create_sewer_room();
    add_exit(SECOND + "s10", "east");
    add_exit(SECOND + "s26", "northwest");
    add_exit(SECOND + "s24", "southwest");

}
