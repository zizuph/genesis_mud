/* A path in the foothills (14). ~mucalytic/hills/locations/path14 */

#include "../defs.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_exit(LOCATIONS + "cave1", "west", 0, 3);
    add_exit(LOCATIONS + "path13", "east", "@@ch_dir@@", 3);
}

void create_room()
{
    ::create_room();

    set_long("You find yourself standing on a large section of path leading "+
        "through the hills. Jagged rocks and small stones litter the area "+
        "and green grass and bushes grown rampant over the terrain. You "+
        "notice that the path continues in a haphazardly eastward but leads "+
        "to a hole in the side of a hill to the west.\n");

    add_item("hole", "The hole in the side of the hill is very large and "+
        "round. It looks like the entrance to a cave of some description. "+
        "The path becomes less overgrown near it.\n");
}

void ch_dir()
{
    write("The path turns northwards.\n\n");
}
