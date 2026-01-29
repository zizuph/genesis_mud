#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f33",
        "southwest" : "r08/f31",
        "south" : "r08/f32",
        "northwest" : "r06/f31",
        "east" : "r07/f33",
        "north" : "r06/f32",
        "northeast" : "r06/f33",
        "west" : "r07/f31",
    ]));
    
}
