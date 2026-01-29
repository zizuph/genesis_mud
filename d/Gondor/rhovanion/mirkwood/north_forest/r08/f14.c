#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(88);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r07/f15",
        "southwest" : "r07/f13",
        "south" : "r07/f14",
        "northwest" : "r09/f13",
        "east" : "r08/f15",
        "north" : "r09/f14",
        "northeast" : "r09/f15",
        "west" : "r08/f13",
    ]));
    
}
