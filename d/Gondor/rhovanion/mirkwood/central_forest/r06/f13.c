#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r05/f14",
        "southwest" : "r05/f12",
        "south" : "r05/f13",
        "northwest" : "r07/f12",
        "east" : "r06/f14",
        "north" : "r07/f13",
        "northeast" : "r07/f14",
        "west" : "r06/f12",
    ]));
    
}
