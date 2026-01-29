#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_NORTH_FOREST_DIR + "r01/f25",
        "west"      : MIRKWOOD_ELFPATH_DIR + "p25",
        "north"     : MIRKWOOD_ELFPATH_DIR + "p26",
        "northeast" : MIRKWOOD_ELFPATH_DIR + "p27",

        "southeast" : "r17/f27",
        "southwest" : "r17/f25",
        "south" : "r17/f26",
        "east" : "r18/f27",
    ]));
    
}
