#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(63);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r06/f22",
        "southwest" : "r06/f20",
        "south" : "r06/f21",
        "northwest" : "r08/f20",
        "east" : "r07/f22",
        "north" : "r08/f21",
        "northeast" : "r08/f22",
        "west" : "r07/f20",
    ]));
    
}
