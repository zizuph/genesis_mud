inherit "/std/room";
#include <macros.h>

create_room()
{
    set_short("The endless wastes");
    set_long("The wastes seem to go on forever. The plains are "+
             "basically lifeless. Hills rise and fall gently and "+
             "majestically off into the distance. Not many could "+
             "love this land, but apparently some do.\n");


    if (LOAD_ERR("/d/Cirath/katakoro/wastes/area_handler/area_handler"))
    {
        write("Can't load map handler, please report immediately...\n");
        return;
    }

    add_exit("", "east", "@@enter_map:/d/Cirath/katakoro/wastes/area_handler/area_handler|A@@");
    add_exit("", "south", "@@enter_map:/d/Cirath/katakoro/wastes/area_handler/area_handler|A@@");
}

