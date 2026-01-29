/* A path in the foothills (25). ~mucalytic/hills/locations/path25 */

#include "../defs.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_exit(LOCATIONS + "path22", "south", 0, 3);
    add_exit(LOCATIONS + "path23", "west", "@@ch_dir1@@", 3);
    add_exit(LOCATIONS + "jetty1", "north", "@@ch_dir2@@", 3);
}

void ch_dir1()
{
    write("The path twists round a small hill and turns southwards.\n\n");
}

void ch_dir2()
{
    write("The path slopes downwards slightly then becomes more sandy. You "+
        "follow it round a small pool of water and turn east.\n\n");
}

