#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(87);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r06/m33",
        "southwest" : "r06/m31",
        "south" : "r06/m32",
        "northwest" : "r08/f31",
        "east" : "r07/f33",
        "north" : "r08/f32",
        "northeast" : "r08/f33",
        "west" : "r07/f31",
    ]));
    
}
