#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(95);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f33",
        "southwest" : "r02/f31",
        "south" : "r02/f32",
        "northwest" : "r04/f31",
        "east" : "r03/f33",
        "north" : "r04/f32",
        "northeast" : "r04/m33",
        "west" : "r03/f31",
    ]));
    
}
