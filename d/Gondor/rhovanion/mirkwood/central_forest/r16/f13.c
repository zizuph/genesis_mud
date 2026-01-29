#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r15/f14",
        "southwest" : "r15/f12",
        "south" : "r15/f13",
        "northwest" : "r17/f12",
        "east" : "r16/f14",
        "north" : "r17/f13",
        "northeast" : "r17/f14",
        "west" : "r16/f12",
    ]));
    
}
