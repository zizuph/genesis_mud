#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/sewers/local.h"

inherit DWARF_TUNNEL;

void
create_sewer_room()
{
    ::create_sewer_room();
    add_exit(SECOND + "s23", "southeast");
    add_exit(SECOND + "s27", "north");
    add_exit(SECOND + "s28", "west");
    
    add_exit(FIRST + "s5", "up");
}
