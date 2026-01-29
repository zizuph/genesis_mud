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
        "northwest" : MIRKWOOD_OLDROAD_DIR + "r36",
        "north" : MIRKWOOD_OLDROAD_DIR + "r37",
        "northeast" : MIRKWOOD_OLDROAD_DIR + "r38",

        "southeast" : "r01/p43",
        "southwest" : "r01/f41",
        "south" : "r01/f42",
        "east" : "r00/f43",
        "west" : "r00/f41",
    ]));
    
}
