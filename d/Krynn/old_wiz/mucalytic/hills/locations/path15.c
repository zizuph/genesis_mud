/* A path in the foothills (15). ~mucalytic/hills/locations/path15 */

#include "../defs.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_exit(LOCATIONS + "path13", "east", 0, 3);
    add_exit(LOCATIONS + "path16", "west", "@@ch_dir@@", 3);
}

void ch_dir()
{
    write("The path runs through a small crevice in the hillside and you "+
        "come out facing north.\n\n");
}
