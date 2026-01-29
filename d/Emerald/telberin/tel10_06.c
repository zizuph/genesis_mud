#include "defs.h";

inherit TELBERIN_SAVENUE;

void
create_south_avenue()
{

    set_short("South Avenue of Telberin");
    set_em_long("This is the South Avenue of Telberin, which passes between "+
        "two of the city's famous gardens. The street is filled with soft "+
        "fragrances from the gardens. Traveling north takes you to the Royal "+
        "Circle and to the Keepers of Telberin. If you travel south you will "+
        "reach the Ri Circle.\n");


    add_exit("tel10_05", "south");
    add_exit("tel10_07", "north");
}