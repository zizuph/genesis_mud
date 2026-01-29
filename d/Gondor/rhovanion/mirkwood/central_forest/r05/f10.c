#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r04/f11",
        "southwest" : "r04/f09",
        "south" : "r04/f10",
        "northwest" : "r06/f09",
        "east" : "r05/f11",
        "north" : "r06/f10",
        "northeast" : "r06/f11",
        "west" : "r05/f09",
    ]));
    
}
