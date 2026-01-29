/* A path in the foothills (21). ~mucalytic/hills/locations/path21 */

#include "../defs.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_boulder();

    add_exit(LOCATIONS + "path27", "west", 0, 3);
    add_exit(LOCATIONS + "path20", "east", "@@ch_dir@@", 3);
}

void init()
{
    ::init();

    init_seat();
}

void ch_dir()
{
    write("The path turns northwards.\n\n");
}

