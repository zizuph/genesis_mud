/* A path in the foothills (20). ~mucalytic/hills/locations/path20 */

#include "../defs.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_exit(LOCATIONS + "path18", "north", 0, 3);
    add_exit(LOCATIONS + "path21", "south", "@@ch_dir@@", 3);
}

void ch_dir()
{
    write("The path turns westwards.\n\n");
}

