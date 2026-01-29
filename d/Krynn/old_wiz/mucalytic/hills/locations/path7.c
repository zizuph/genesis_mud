/* A path in the foothills (7). ~mucalytic/hills/locations/path7 */

#include "../defs.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_exit(LOCATIONS + "path8", "east", 0, 3);
    add_exit(LOCATIONS + "path5", "south", "@@ch_dir@@", 3);
}

void ch_dir()
{
    write("The path turns eastwards as it meanders between two large hills.\n\n");
}
