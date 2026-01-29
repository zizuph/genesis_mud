#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest38", "northwest");
    add_exit(FOREST + "forest39", "north");
    add_exit(FOREST + "forest40", "northeast");
    add_exit("/d/Krynn/ergoth/south/roads/rooms/pier0", "south");
}
