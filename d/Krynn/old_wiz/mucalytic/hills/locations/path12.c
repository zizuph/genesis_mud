/* A path in the foothills (12). ~mucalytic/hills/locations/path12 */

#include "../defs.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_exit(LOCATIONS + "path11", "east", 0, 3);
    add_exit(LOCATIONS + "path10", "west", "@@ch_dir@@", 3);
}

void ch_dir()
{
    write("The path swings southwards to avoid a large boulder.\n\n");
}
