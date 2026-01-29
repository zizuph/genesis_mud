#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r07/f49",
        "southwest" : "r07/f47",
        "south" : "r07/f48",
        "northwest" : "r05/f47",
        "east" : "r06/f49",
        "north" : "r05/f48",
        "northeast" : "r05/f49",
        "west" : "r06/f47",
    ]));
    
}
