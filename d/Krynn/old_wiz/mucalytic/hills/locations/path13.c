/* A path in the foothills (13). ~mucalytic/hills/locations/path13 */

#include "../defs.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_boulder();

    add_exit(LOCATIONS + "path6", "east", 0, 3);
    add_exit(LOCATIONS + "path15", "west", 0, 3);
    add_exit(LOCATIONS + "path14", "south", "@@ch_dir@@", 3);
}

void init()
{
    ::init();

    init_seat();
}

void ch_dir()
{
    write("The path turns westwards.\n\n");
}
