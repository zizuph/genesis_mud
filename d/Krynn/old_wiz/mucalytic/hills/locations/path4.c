/* A path in the foothills (4). ~mucalytic/hills/locations/path4 */

#include "../defs.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_exit(LOCATIONS + "path5", "west", 0, 3);
    add_exit(LOCATIONS + "path2", "north", 0, 3);
    add_exit(LOCATIONS + "path6", "south", 0, 3);
}
