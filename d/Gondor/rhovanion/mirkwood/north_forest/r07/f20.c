#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(50);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r06/f21",
        "southwest" : "r06/f19",
        "south" : "r06/f20",
        "northwest" : "r08/f19",
        "east" : "r07/f21",
        "north" : "r08/f20",
        "northeast" : "r08/f21",
        "west" : "r07/f19",
    ]));
    
}
