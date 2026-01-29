#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f49",
        "southwest" : "r04/f47",
        "south" : "r04/f48",
        "northwest" : "r06/f47",
        "east" : "r05/f49",
        "north" : "r06/f48",
        "northeast" : "r06/f49",
        "west" : "r05/f47",
    ]));
    
}
