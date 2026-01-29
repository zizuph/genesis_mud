/* A path in the foothills (16). ~mucalytic/hills/locations/path16 */

#include "../defs.h"

inherit STD + "hill_path";

void reset_room()
{
    add_money();
}

void create_hill_path()
{
    add_exit(LOCATIONS + "path17", "north", 0, 3);
    add_exit(LOCATIONS + "path15", "south", "@@ch_dir@@", 3);

    reset_room();
}

void ch_dir()
{
    write("The path runs through a small crevice in the hillside and you "+
        "come out facing east.\n\n");
}
