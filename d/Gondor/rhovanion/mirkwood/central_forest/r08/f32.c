#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(37);

    set_distance_to_edge(8);
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
