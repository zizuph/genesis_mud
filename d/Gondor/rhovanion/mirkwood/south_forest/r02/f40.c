#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r03/f41",
        "southwest" : "r03/f39",
        "south" : "r03/f40",
        "northwest" : "r01/f39",
        "east" : "r02/f41",
        "north" : "r01/f40",
        "northeast" : "r01/f41",
        "west" : "r02/f39",
    ]));
    
}
