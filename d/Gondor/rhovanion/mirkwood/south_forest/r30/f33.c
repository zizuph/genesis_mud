#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r31/f34",
        "southwest" : "r31/f32",
        "south" : "r31/f33",
        "northwest" : "r29/f32",
        "east" : "r30/f34",
        "north" : "r29/f33",
        "northeast" : "r29/f34",
        "west" : "r30/f32",
    ]));
    
}
