#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r03/f20",
        "southwest" : "r03/f18",
        "south" : "r03/f19",
        "northwest" : "r01/f18",
        "east" : "r02/f20",
        "north" : "r01/f19",
        "northeast" : "r01/f20",
        "west" : "r02/f18",
    ]));
    
}
