#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(51);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f39",
        "southwest" : "r01/f37",
        "south" : "r01/f38",
        "northwest" : "r03/f37",
        "east" : "r02/f39",
        "north" : "r03/f38",
        "northeast" : "r03/f39",
        "west" : "r02/f37",
    ]));
    
}
