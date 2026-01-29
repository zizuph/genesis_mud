#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r01/f10",
        "southwest" : "r01/f08",
        "south" : "r01/f09",
        "northwest" : "r03/f08",
        "east" : "r02/f10",
        "north" : "r03/f09",
        "northeast" : "r03/f10",
        "west" : "r02/f08",
    ]));
    
}
