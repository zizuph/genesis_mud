/* A path in the foothills (30). ~mucalytic/hills/locations/path30 */

#include "../defs.h"

inherit STD + "hill_path";

void reset_room()
{
    add_money();
}

void create_hill_path()
{
    add_exit(LOCATIONS + "path28", "east", 0, 3);
    add_exit(LOCATIONS + "path27", "west", "@@ch_dir@@", 3);

    reset_room();
}

void ch_dir()
{
    write("The runs around the side of a hill until you're facing north.\n\n");
}
