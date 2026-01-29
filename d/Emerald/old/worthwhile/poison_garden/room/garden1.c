#include "../garden.h"

inherit GARDEN_BASE;

void create_garden_room()
{
    set_long("Garden room\n");
    add_garden_exit(1, "garden2", "north");
    add_garden_exit(2, "garden3", "east");
    add_garden_exit(2, "garden4", "west");
}
