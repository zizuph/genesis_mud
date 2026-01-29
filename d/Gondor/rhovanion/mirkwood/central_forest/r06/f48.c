#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r05/f49",
        "southwest" : "r05/f47",
        "south" : "r05/f48",
        "northwest" : "r07/f47",
        "east" : "r06/f49",
        "north" : "r07/f48",
        "northeast" : "r07/f49",
        "west" : "r06/f47",
    ]));
    
}
