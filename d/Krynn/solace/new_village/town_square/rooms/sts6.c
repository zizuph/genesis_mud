/*
* STS Room 6
* Created by Leia
* May 30, 2005
*/

/*
** Last Updated By:
** Leia
** July 1, 2005
*/

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit SQUARE_BASE;

void
reset_solace_room()
{
}

void
create_solace_room()
{
    set_add_trees();
    set_add_buildings();
    add_exit(NORTHSTS6, "north");
    add_exit(SOUTHSTS6, "south");
    add_exit(ROOM7, "east");
    add_exit(ROOM5, "west");
    add_exit(NESTS6, "northeast");
    add_exit(ROOM3, "northwest");
    reset_solace_room();
}
