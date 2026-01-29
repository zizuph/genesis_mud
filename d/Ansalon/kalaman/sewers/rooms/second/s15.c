#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/sewers/local.h"

inherit DWARF_VILLAGE;

void
create_sewer_room()
{
    ::create_sewer_room();
    add_exit(SECOND + "s13", "north");
    add_exit(SECOND + "s16", "east");
}
