#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/sewers/local.h"

inherit SEWER_IN;

void
create_sewer_room()
{
    ::create_sewer_room();
    add_exit(FIRST + "s29", "northeast");
    add_exit(FIRST + "s27", "southwest");
    add_exit(FIRST + "s30", "north");
}
