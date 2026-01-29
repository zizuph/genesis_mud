#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(63);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f37",
        "southwest" : "r01/f35",
        "south" : "r01/f36",
        "northwest" : "r03/m35",
        "east" : "r02/f37",
        "north" : "r03/m36",
        "northeast" : "r03/f37",
        "west" : "r02/f35",
    ]));
    
}
