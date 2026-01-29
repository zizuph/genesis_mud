#include "defs.h"

inherit TELBERIN_ARTISANS_WAY;

public void
create_artisans_way()
{
    set_em_long("The long stretch of Artisans Way makes a gentle arc through " +
        "the Mercantile quarter of Telberin, passing countless business " +
        "offices, shops, and outdoor markets along its northern edge.  " +
        "South, a sprawling green extends the entire length of the quarter, " +
        "from the western gates of the city to gates of the towering royal " +
        "palace at the city's center.\n");

    add_exit("artisans_way03", "west");
    add_exit("artisans_way01", "east");
}
