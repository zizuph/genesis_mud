#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r05/f33",
        "southwest" : "r06/f31",
        "south" : "r05/f32",
        "northwest" : "r07/f31",
        "east" : "r06/f33",
        "north" : "r07/f32",
        "northeast" : "r07/f33",
        "west" : "r06/f31",
    ]));
    
}
