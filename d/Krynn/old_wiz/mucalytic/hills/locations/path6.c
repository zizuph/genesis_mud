/* A path in the foothills (6). ~mucalytic/hills/locations/path6 */

#include "../defs.h"

inherit STD + "hill_path";

void reset_room()
{
    add_birds();
}

void create_hill_path()
{
    add_exit(LOCATIONS + "path13", "west", 0, 3);
    add_exit(LOCATIONS + "path4", "north", 0, 3);

    reset_room();
}
