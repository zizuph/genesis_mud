#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(56);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r06/f19",
        "southwest" : "r06/f17",
        "south" : "r06/f18",
        "northwest" : "r08/f17",
        "east" : "r07/f19",
        "north" : "r08/f18",
        "northeast" : "r08/f19",
        "west" : "r07/f17",
    ]));
    
}
