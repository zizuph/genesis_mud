#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(69);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f31",
        "southwest" : "r01/f29",
        "south" : "r01/f30",
        "northwest" : "r03/f29",
        "east" : "r02/f31",
        "north" : "r03/f30",
        "northeast" : "r03/f31",
        "west" : "r02/f29",
    ]));
    
}
