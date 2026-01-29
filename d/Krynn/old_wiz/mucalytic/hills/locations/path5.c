/* A path in the foothills (5). ~mucalytic/hills/locations/path5 */

#include "../defs.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_boulder();

    add_exit(LOCATIONS + "path4", "east", 0, 3);
    add_exit(LOCATIONS + "path7", "west", "@@ch_dir@@", 3);
}

void init()
{
    ::init();

    init_seat();
}

void ch_dir()
{
    write("The path turns northwards as it meanders between two large hills.\n\n");
}
