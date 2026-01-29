#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "path";

void create_mirkwood_south_forest_path_room() {

    add_long("The small path you are on twists its way through " +
        "the trees from the northwest to the southeast. ",
        ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));

    add_item_light(({"path","well-worn path","small path"}),
        "This small, well-worn path travels from the northwest to the " +
        "southeast.\n", LIGHT_ALL);

    add_mirkwood_exits(([
        "southeast" : "/d/Gondor/rhovanion/mirkwood/goblins/hargnak1",
        "southwest" : "r02/f42",
        "south" : "r02/f43",
        "northwest" : "r00/p42",
        "east" : "r01/f44",
        "north" : "r00/f43",
        "northeast" : "r00/f44",
        "west" : "r01/f42",
    ]));
    
}
