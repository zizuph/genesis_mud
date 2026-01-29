/* A path in the foothills (2). ~mucalytic/hills/locations/path2 */

#include "../defs.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_boulder();

    add_exit(LOCATIONS + "path1", "east", 0, 3);
    add_exit(LOCATIONS + "path3", "north", 0, 3);
    add_exit(LOCATIONS + "path4", "south", 0, 3);
}

void init()
{
    ::init();

    init_seat();
}
