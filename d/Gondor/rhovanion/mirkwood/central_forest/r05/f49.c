#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r04/f50",
        "southwest" : "r04/f48",
        "south" : "r04/f49",
        "northwest" : "r06/f48",
        "east" : "r05/f50",
        "north" : "r06/f49",
        "northeast" : "r06/f50",
        "west" : "r05/f48",
    ]));
    
}
