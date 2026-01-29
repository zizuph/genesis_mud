#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(49);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r07/f17",
        "southwest" : "r07/f15",
        "south" : "r07/f16",
        "northwest" : "r09/f15",
        "east" : "r08/f17",
        "north" : "r09/f16",
        "northeast" : "r09/f17",
        "west" : "r08/f15",
    ]));
    
}
