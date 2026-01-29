#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_NORTH_FOREST_DIR + "r00/f22",
        "west"      : MIRKWOOD_ELFPATH_DIR + "p22",
        "north"     : MIRKWOOD_ELFPATH_DIR + "p23",
        "northeast" : MIRKWOOD_ELFPATH_DIR + "p24",

        "southeast" : "r16/f24",
        "southwest" : "r16/f22",
        "south" : "r16/f23",
        "east" : "r17/f24",
    ]));
    
}
