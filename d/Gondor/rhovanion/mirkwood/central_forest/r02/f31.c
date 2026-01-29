#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(63);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f32",
        "southwest" : "r01/f30",
        "south" : "r01/f31",
        "northwest" : "r03/f30",
        "east" : "r02/f32",
        "north" : "r03/f31",
        "northeast" : "r03/f32",
        "west" : "r02/f30",
    ]));
    
}
