#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(83);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r08/f13",
        "southwest" : "r08/f11",
        "south" : "r08/f12",
        "northwest" : "r10/f11",
        "east" : "r09/f13",
        "north" : "r10/f12",
        "northeast" : "r10/f13",
        "west" : "r09/f11",
    ]));
    
}
