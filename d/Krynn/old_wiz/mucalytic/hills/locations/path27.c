/* A path in the foothills (27). ~mucalytic/hills/locations/path27 */

#include "../defs.h"

inherit STD + "hill_path";

void create_hill_path()
{
//  add_exit(LOCATIONS + "seats", "west", 0, 3);
    add_exit(LOCATIONS + "path21", "east", 0, 3);
    add_exit(LOCATIONS + "path30", "south", "@@ch_dir@@", 3);
}

void ch_dir()
{
    write("The runs around the side of a hill until you're facing east.\n\n");
}
