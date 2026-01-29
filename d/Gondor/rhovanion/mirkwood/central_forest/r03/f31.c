#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(83);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f32",
        "southwest" : "r02/f30",
        "south" : "r02/f31",
        "northwest" : "r04/f30",
        "east" : "r03/f32",
        "north" : "r04/f31",
        "northeast" : "r04/f32",
        "west" : "r03/f30",
    ]));
    
}
