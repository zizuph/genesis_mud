#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(37);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f25",
        "southwest" : "r01/f23",
        "south" : "r01/f24",
        "northwest" : "r03/f23",
        "east" : "r02/f25",
        "north" : "r03/f24",
        "northeast" : "r03/f25",
        "west" : "r02/f23",
    ]));
    
}
