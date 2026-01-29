#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r04/f48",
        "southwest" : "r04/f46",
        "south" : "r04/f47",
        "northwest" : "r06/f46",
        "east" : "r05/f48",
        "north" : "r06/f47",
        "northeast" : "r06/f48",
        "west" : "r05/f46",
    ]));
    
}
