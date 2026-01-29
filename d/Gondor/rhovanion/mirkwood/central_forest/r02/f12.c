#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f13",
        "southwest" : "r01/f11",
        "south" : "r01/f12",
        "northwest" : "r03/f11",
        "east" : "r02/f13",
        "north" : "r03/f12",
        "northeast" : "r03/f13",
        "west" : "r02/f11",
    ]));
    
}
