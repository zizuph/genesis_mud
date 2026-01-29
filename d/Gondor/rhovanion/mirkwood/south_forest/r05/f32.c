#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f33",
        "southwest" : "r06/f31",
        "south" : "r06/f32",
        "northwest" : "r04/f31",
        "east" : "r05/f33",
        "north" : "r04/f32",
        "northeast" : "r04/f33",
        "west" : "r05/f31",
    ]));
    
}
