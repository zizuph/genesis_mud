#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/sewers/local.h"

inherit DWARF_COTTAGE;

object king;

void
create_sewer_room()
{
    ::create_sewer_room();
    add_exit(SECOND + "s16", "out");
}

void
reset_sewer_room()
{
    ::reset_sewer_room();
    
    if (!objectp(king))
    {
        king = clone_object(MONSTERS + "dwarven_king");
        king->move_living("xxx", TO);
    }
}