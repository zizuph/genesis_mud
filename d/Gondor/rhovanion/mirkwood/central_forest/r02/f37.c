#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(61);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f38",
        "southwest" : "r01/f36",
        "south" : "r01/f37",
        "northwest" : "r03/m36",
        "east" : "r02/f38",
        "north" : "r03/f37",
        "northeast" : "r03/f38",
        "west" : "r02/f36",
    ]));
    
}
