/* A path in the foothills (8). ~mucalytic/hills/locations/path8 */

#include "../defs.h"

inherit STD + "hill_path";

void reset_room()
{
    add_money();
}

void create_hill_path()
{
    add_exit(LOCATIONS + "path7", "west", 0, 3);
    add_exit(LOCATIONS + "path9", "north", 0, 3);

    reset_room();
}
