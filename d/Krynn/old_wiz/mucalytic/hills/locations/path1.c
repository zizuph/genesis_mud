/* A path in the foothills (1). ~mucalytic/hills/locations/path1 */

#include "../defs.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_exit(LOCATIONS + "path2", "west", 0, 3);
    add_exit(LOCATIONS + "link1", "east", 0, 3);
}
