#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r05/f50",
        "southwest" : "r05/f48",
        "south" : "r05/f49",
        "northwest" : "r03/f48",
        "east" : "r04/f50",
        "north" : "r03/f49",
        "northeast" : "r03/f50",
        "west" : "r04/f48",
    ]));
    
}
