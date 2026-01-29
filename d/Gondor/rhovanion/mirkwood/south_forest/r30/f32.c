#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r31/f33",
        "southwest" : "r31/f31",
        "south" : "r31/f32",
        "northwest" : "r29/f31",
        "east" : "r30/f33",
        "north" : "r29/f32",
        "northeast" : "r29/f33",
        "west" : "r30/f31",
    ]));
    
}
