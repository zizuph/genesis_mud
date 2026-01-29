#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f21",
        "southwest" : "r01/f19",
        "south" : "r01/f20",
        "northwest" : "r03/f19",
        "east" : "r02/f21",
        "north" : "r03/f20",
        "northeast" : "r03/f21",
        "west" : "r02/f19",
    ]));
    
}
