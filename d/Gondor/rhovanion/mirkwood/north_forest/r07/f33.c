#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r06/f34",
        "southwest" : "r06/f32",
        "south" : "r06/f33",
        "northwest" : "r08/f32",
        "east" : "r07/f34",
        "north" : "r08/f33",
        "northeast" : "r08/f34",
        "west" : "r07/f32",
    ]));
    
}
