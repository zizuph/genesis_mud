/* A path in the foothills (18). ~mucalytic/hills/locations/path18 */

#include "../defs.h"

inherit STD + "hill_path";

void reset_room()
{
    add_birds();
}

void create_hill_path()
{
    add_exit(LOCATIONS + "path17", "east", 0, 3);
    add_exit(LOCATIONS + "path19", "north", 0, 3);
    add_exit(LOCATIONS + "path20", "south", 0, 3);
    add_exit(LOCATIONS + "path26", "west", "@@ch_dir@@", 3);

    reset_room();
}

void ch_dir()
{
    write("The path runs round the base of a hill, leading you southwards.\n\n");
}
