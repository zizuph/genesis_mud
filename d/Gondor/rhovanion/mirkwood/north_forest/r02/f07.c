#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r01/f08",
        "southwest" : "r01/f06",
        "south" : "r01/f07",
        "northwest" : "r03/f06",
        "east" : "r02/f08",
        "north" : "r03/f07",
        "northeast" : "r03/f08",
        "west" : "r02/f06",
    ]));
    
}
