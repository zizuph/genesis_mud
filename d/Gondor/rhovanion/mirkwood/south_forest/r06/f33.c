#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r07/f34",
        "southwest" : "r07/f32",
        "south" : "r07/f33",
        "northwest" : "r05/f32",
        "east" : "r06/f34",
        "north" : "r05/f33",
        "northeast" : "r05/f34",
        "west" : "r06/f32",
    ]));
    
}
