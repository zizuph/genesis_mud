/* A path in the foothills (29). ~mucalytic/hills/locations/path29 */

#include "../defs.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_boulder();

    add_exit(LOCATIONS + "path19", "west", "@@ch_dir1@@", 3);
    add_exit(LOCATIONS + "jetty1", "north", "@@ch_dir2@@", 3);
}

void init()
{
    ::init();

    init_seat();
}

void ch_dir1()
{
    write("The path twists and winds and you end up facing southwards.\n\n");
}

void ch_dir2()
{
    write("The path slopes downwards slightly then becomes more sandy. You "+
        "follow it past some obstructing rocks and turn west.\n\n");
}

