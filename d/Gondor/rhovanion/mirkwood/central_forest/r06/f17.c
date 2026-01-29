#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(53);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r05/f18",
        "southwest" : "r05/f16",
        "south" : "r05/f17",
        "northwest" : "r07/f16",
        "east" : "r06/f18",
        "north" : "r07/f17",
        "northeast" : "r07/f18",
        "west" : "r06/f16",
    ]));
    
}
