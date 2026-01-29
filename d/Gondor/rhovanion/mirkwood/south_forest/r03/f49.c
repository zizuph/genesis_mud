#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r04/f50",
        "southwest" : "r04/f48",
        "south" : "r04/f49",
        "northwest" : "r02/f48",
        "east" : "r03/f50",
        "north" : "r02/f49",
        "northeast" : "r02/f50",
        "west" : "r03/f48",
    ]));
    
}
