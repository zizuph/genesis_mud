#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(36);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r07/f21",
        "southwest" : "r07/f19",
        "south" : "r07/f20",
        "northwest" : "r09/f19",
        "east" : "r08/f21",
        "north" : "r09/f20",
        "northeast" : "r09/f21",
        "west" : "r08/f19",
    ]));
    
}
