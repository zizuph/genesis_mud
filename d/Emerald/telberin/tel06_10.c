#include "defs.h";

inherit TELBERIN_WAVENUE;

void
create_west_avenue()
{
    set_short("West Avenue of Telberin");
    set_em_long("This is the West Avenue of Telberin, which passes between two "+
        "of the city's famous gardens. The street is filled with soft fragrances "+
        "from the gardens. Traveling west takes you to the west gate and to the "+
        "east you will find the gates of the Royal Palace.\n");

    add_item(({"garden", "gardens"}),
        "You are between two of Telberin’s famous gardens. The sweet fragrances "+
        "linger softly in the air filling you with anticipation.\n");

    add_item(({"fragrance", "fragrances"}),
        "The sweet fragrance of roses and honeysuckle is much stronger here.\n");

    add_exit("tel05_10", "west");
    add_exit("tel07_10", "east");
}
