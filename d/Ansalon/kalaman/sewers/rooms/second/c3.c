#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/sewers/local.h"

inherit DWARF_COTTAGE;

void
create_sewer_room()
{
    ::create_sewer_room();
    add_exit(SECOND + "s21", "out");
}
