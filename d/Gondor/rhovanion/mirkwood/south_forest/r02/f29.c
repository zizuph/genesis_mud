#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r03/f30",
        "southwest" : "r03/f28",
        "south" : "r03/f29",
        "northwest" : "r01/f28",
        "east" : "r02/f30",
        "north" : "r01/f29",
        "northeast" : "r01/f30",
        "west" : "r02/f28",
    ]));
    
}
