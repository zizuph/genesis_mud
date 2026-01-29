#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r09/f34",
        "southwest" : "r09/f32",
        "south" : "r09/f33",
        "northwest" : "r07/f32",
        "east" : "r08/f34",
        "north" : "r07/f33",
        "northeast" : "r07/f34",
        "west" : "r08/f32",
    ]));
    
}
