#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/sewers/local.h"

inherit DWARF_TUNNEL;

void
create_sewer_room()
{
    ::create_sewer_room();
    add_exit(SECOND + "s23", "northeast");
    add_exit(SECOND + "s25", "south");
}
