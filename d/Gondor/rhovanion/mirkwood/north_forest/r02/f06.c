#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r01/f07",
        "southwest" : "r01/f05",
        "south" : "r01/f06",
        "northwest" : "r03/f05",
        "east" : "r02/f07",
        "north" : "r03/f06",
        "northeast" : "r03/f07",
        "west" : "r02/f05",
    ]));
    
}
