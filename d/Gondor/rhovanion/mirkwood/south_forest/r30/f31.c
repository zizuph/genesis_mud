#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r31/f32",
        "southwest" : "r31/f30",
        "south" : "r31/f31",
        "northwest" : "r29/f30",
        "east" : "r30/f32",
        "north" : "r29/f31",
        "northeast" : "r29/f32",
        "west" : "r30/f30",
    ]));
    
}
