#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p16",
        "north"     : MIRKWOOD_ELFPATH_DIR + "p17",
        "east"      : MIRKWOOD_ELFPATH_DIR + "p18",
        "northeast" : MIRKWOOD_NORTH_FOREST_DIR + "r00/f18",

        "southeast" : "r16/f18",
        "southwest" : "r16/f16",
        "south" : "r16/f17",
        "west" : "r17/f16",
    ]));
    
}
