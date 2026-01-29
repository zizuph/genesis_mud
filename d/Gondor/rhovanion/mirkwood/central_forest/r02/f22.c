#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(38);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f23",
        "southwest" : "r01/f21",
        "south" : "r01/f22",
        "northwest" : "r03/f21",
        "east" : "r02/f23",
        "north" : "r03/f22",
        "northeast" : "r03/f23",
        "west" : "r02/f21",
    ]));
    
}
