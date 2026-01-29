/* A path in the foothills (9). ~mucalytic/hills/locations/path9 */

#include "../defs.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_boulder();

    add_exit(LOCATIONS + "path10", "west", 0, 3);
    add_exit(LOCATIONS + "path8", "south", 0, 3);
}

void init()
{
    ::init();

    init_seat();
}
