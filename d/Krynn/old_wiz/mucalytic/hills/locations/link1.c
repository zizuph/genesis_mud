/* Beginning of the foothills. ~mucalytic/hills/locations/link1 */

#include "../defs.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_exit(OUTSIDE + "lane4", "east", 0, 2);
    add_exit(LOCATIONS + "path1", "west", 0, 3);
}

void create_room()
{
    ::create_room();

    set_long("You find that the region of land around you is slowly becoming "+
        "more an more hilly and undulating in nature. The path that you are "+
        "standing on starts to become more overgrown with grass the further "+
        "west you go. Back to the east you can see a large city in the "+
        "distance.\n");
}
