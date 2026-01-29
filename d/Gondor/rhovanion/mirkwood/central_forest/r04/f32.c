#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(80);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f33",
        "southwest" : "r03/f31",
        "south" : "r03/f32",
        "northwest" : "r05/m31",
        "east" : "r04/m33",
        "north" : "r05/m32",
        "northeast" : "r05/m33",
        "west" : "r04/f31",
    ]));
    
}
