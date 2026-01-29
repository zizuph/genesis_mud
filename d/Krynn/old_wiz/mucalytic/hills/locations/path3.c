/* A path in the foothills (3). ~mucalytic/hills/locations/path3 */

#include "../defs.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_exit(LOCATIONS + "path2", "south", 0, 3);
    add_exit(LOCATIONS + "path11", "north", 0, 3);
}
