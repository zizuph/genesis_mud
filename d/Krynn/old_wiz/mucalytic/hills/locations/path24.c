/* A path in the foothills (24). ~mucalytic/hills/locations/path24 */

#include "../defs.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_exit(LOCATIONS + "path23", "north", 0, 3);
    add_exit(LOCATIONS + "notice_board", "west", 0, 3);
    add_exit(LOCATIONS + "path26", "south", "@@ch_dir@@", 3);
}

void ch_dir()
{
    write("The path runs through a small cave in the side of a hill and you "+
        "end up facing east.\n\n");
}
