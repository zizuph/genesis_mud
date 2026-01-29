#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r05/f50",
        "southwest" : "r05/f48",
        "south" : "r05/f49",
        "northwest" : "r07/f48",
        "east" : "r06/f50",
        "north" : "r07/f49",
        "northeast" : "r07/f50",
        "west" : "r06/f48",
    ]));
    
}
