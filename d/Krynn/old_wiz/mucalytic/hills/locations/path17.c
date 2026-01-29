/* A path in the foothills (17). ~mucalytic/hills/locations/path17 */

#include "../defs.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_boulder();

    add_exit(LOCATIONS + "path18", "west", 0, 3);
    add_exit(LOCATIONS + "path16", "south", 0, 3);
    add_exit(LOCATIONS + "path10", "north", "@@ch_dir@@", 3);
}

void init()
{
    ::init();

    init_seat();
}

void ch_dir()
{
    write("The path turns to the east.\n\n");
}
