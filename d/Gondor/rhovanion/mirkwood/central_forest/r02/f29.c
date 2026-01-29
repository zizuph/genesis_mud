#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(62);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f30",
        "southwest" : "r01/f28",
        "south" : "r01/f29",
        "northwest" : "r03/f28",
        "east" : "r02/f30",
        "north" : "r03/f29",
        "northeast" : "r03/f30",
        "west" : "r02/f28",
    ]));
    
}
