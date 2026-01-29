#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/sewers/local.h"

inherit DWARF_VILLAGE;

void
create_sewer_room()
{
    ::create_sewer_room();
    add_exit(SECOND + "s17", "southwest");
    add_exit(SECOND + "s18", "west");
    add_exit(SECOND + "s20", "east");
    add_exit(SECOND + "s21", "north");

}
