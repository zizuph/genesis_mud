#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r03/f32",
        "southwest" : "r03/f30",
        "south" : "r03/f31",
        "northwest" : "r05/f30",
        "east" : "r04/f32",
        "north" : "r05/f31",
        "northeast" : "r05/f31",
        "west" : "r04/f30",
    ]));
    
}
