#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(51);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r06/f18",
        "southwest" : "r06/f16",
        "south" : "r06/f17",
        "northwest" : "r08/f16",
        "east" : "r07/f18",
        "north" : "r08/f17",
        "northeast" : "r08/f18",
        "west" : "r07/f16",
    ]));
    
}
