/* A path in the foothills (11). ~mucalytic/hills/locations/path11 */

#include "../defs.h"

inherit STD + "hill_path";

void reset_room()
{
    add_birds();
}

void create_hill_path()
{
    add_exit(LOCATIONS + "path12", "west", 0, 3);
    add_exit(LOCATIONS + "path3", "south", 0, 3);

    reset_room();
}
