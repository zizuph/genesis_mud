#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r04/f51",
        "southwest" : "r04/f49",
        "south" : "r04/f50",
        "northwest" : "r06/f49",
        "east" : "r05/f51",
        "north" : "r06/f50",
        "northeast" : "r06/f51",
        "west" : "r05/f49",
    ]));
    
}
