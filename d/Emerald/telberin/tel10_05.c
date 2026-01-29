#include "defs.h";

inherit TELBERIN_SAVENUE;

void
create_south_avenue()
{

    set_short("South Avenue of Telberin");
    set_em_long("This is the South Avenue of Telberin, which passes between "+
        "two of the city's famous gardens. The street is filled with soft "+
        "fragrances from the gardens. The north takes you to the Royal Circle "+
        "and to the Keepers of Telberin.\n");

    add_exit("tel10_04", "south");
    add_exit("tel10_06", "north");
}