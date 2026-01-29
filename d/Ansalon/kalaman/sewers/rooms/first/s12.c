#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/sewers/local.h"

inherit SEWER_IN;

void
create_sewer_room()
{
    ::create_sewer_room();
    add_exit(FIRST + "s16", "northwest");
    add_exit(FIRST + "s13", "northeast");
    add_exit(FIRST + "s10", "southwest");
    add_exit(FIRST + "s11", "southeast");
   
}
