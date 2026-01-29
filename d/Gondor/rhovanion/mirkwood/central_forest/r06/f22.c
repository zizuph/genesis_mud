#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(96);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r05/m23",
        "southwest" : "r05/f21",
        "south" : "r05/m22",
        "northwest" : "r07/f21",
        "east" : "r06/f23",
        "north" : "r07/f22",
        "northeast" : "r07/f23",
        "west" : "r06/f21",
    ]));
    
}
