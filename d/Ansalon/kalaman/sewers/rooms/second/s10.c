#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/sewers/local.h"

inherit DWARF_TUNNEL;

void
create_sewer_room()
{
    ::create_sewer_room();
    add_exit(SECOND + "s9", "northeast");
    add_exit(SECOND + "s23", "west");
    add_exit(SECOND + "s11", "southeast");

}
