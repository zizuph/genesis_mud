#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r03/f03",
        "southwest" : "r03/f01",
        "south" : "r03/f02",
        "northwest" : "r05/f01",
        "east" : "r04/f03",
        "north" : "r05/f02",
        "northeast" : "r05/f03",
        "west" : "r04/f01",
    ]));
    
}
