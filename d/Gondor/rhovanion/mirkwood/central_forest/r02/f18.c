#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f19",
        "southwest" : "r01/f17",
        "south" : "r01/f18",
        "northwest" : "r03/f17",
        "east" : "r02/f19",
        "north" : "r03/f18",
        "northeast" : "r03/f19",
        "west" : "r02/f17",
    ]));
    
}
