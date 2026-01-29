/* A path in the foothills (22). ~mucalytic/hills/locations/path22 */

#include "../defs.h"

inherit STD + "hill_path";

void reset_room()
{
    add_birds();
}

void create_hill_path()
{
    add_exit(LOCATIONS + "path19", "east", 0, 3);
    add_exit(LOCATIONS + "path23", "west", 0, 3);
    add_exit(LOCATIONS + "path25", "north", 0, 3);

    reset_room();
}
