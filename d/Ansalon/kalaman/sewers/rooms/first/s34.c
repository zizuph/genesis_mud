#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/sewers/local.h"

inherit SEWER_IN;

void
create_sewer_room()
{
    ::create_sewer_room();
    add_exit(FIRST + "s33", "southeast");
    add_exit(FIRST + "s35", "north");
    add_exit(FIRST + "s36", "northwest");
}
