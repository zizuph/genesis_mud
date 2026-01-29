#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(79);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r07/f34",
        "southwest" : "r07/f32",
        "south" : "r07/f33",
        "northwest" : "r09/f32",
        "east" : "r08/f34",
        "north" : "r09/f33",
        "northeast" : "r09/f34",
        "west" : "r08/f32",
    ]));
    
}
