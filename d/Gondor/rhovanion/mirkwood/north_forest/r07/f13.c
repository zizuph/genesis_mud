#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(32);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r06/f14",
        "southwest" : "r06/f12",
        "south" : "r06/f13",
        "northwest" : "r08/f12",
        "east" : "r07/f14",
        "north" : "r08/f13",
        "northeast" : "r08/f14",
        "west" : "r07/f12",
    ]));
    
}
