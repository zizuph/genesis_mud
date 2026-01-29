#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r03/f31",
        "southwest" : "r03/f29",
        "south" : "r03/f30",
        "northwest" : "r01/f29",
        "east" : "r02/f31",
        "north" : "r01/f30",
        "northeast" : "r01/f31",
        "west" : "r02/f29",
    ]));
    
}
