/* A path in the foothills (19). ~muclytic/hills/locations/path19 */

#include "../defs.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_boulder();

    add_exit(LOCATIONS + "path22", "west", 0, 3);
    add_exit(LOCATIONS + "path18", "south", 0, 3);
    add_exit(LOCATIONS + "path29", "north", "@@ch_dir@@", 3);
}

void init()
{
    ::init();

    init_seat();
}

void ch_dir()
{
    write("The path twists and winds and you end up facing eastwards.\n\n");
}
