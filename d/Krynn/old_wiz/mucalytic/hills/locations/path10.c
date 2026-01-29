/* A path in the foothills (10). ~mucalytic/hills/locations/path10 */

#include "../defs.h"

inherit STD + "hill_path";

void reset_room()
{
    add_birds();
}

void create_hill_path()
{
    add_exit(LOCATIONS + "path9", "east", 0, 3);
    add_exit(LOCATIONS + "path17", "west", "@@ch_dir1@@", 3);
    add_exit(LOCATIONS + "path12", "north", "@@ch_dir2@@", 3);

    reset_room();
}

void ch_dir1()
{
    write("The path turns to the south.\n\n");
}

void ch_dir2()
{
    write("The path swings eastwards to avoid a large boulder.\n\n");
}
