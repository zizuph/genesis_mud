/* A path in the foothills (23). ~mucalytic/hills/locations/path23 */

#include "../defs.h"

inherit STD + "hill_path";

void reset_room()
{
    add_money();
}

void create_hill_path()
{
    add_exit(LOCATIONS + "path22", "east", 0, 3);
    add_exit(LOCATIONS + "path24", "south", 0, 3);
    add_exit(LOCATIONS + "path25", "north", "@@ch_dir@@", 3);

    reset_room();
}

void ch_dir()
{
    write("The path twists round a small hill and turns eastwards.\n\n");
}

