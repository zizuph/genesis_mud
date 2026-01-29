#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r07/f33",
        "southwest" : "r07/f31",
        "south" : "r07/f32",
        "northwest" : "r09/f31",
        "east" : "r08/f33",
        "north" : "r09/f32",
        "northeast" : "r09/f33",
        "west" : "r08/f31",
    ]));
    
}
