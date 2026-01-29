#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r04/f51",
        "southwest" : "r04/f49",
        "south" : "r04/f50",
        "northwest" : "r02/f49",
        "east" : "r03/f51",
        "north" : "r02/f50",
        "northeast" : "r02/f51",
        "west" : "r03/f49",
    ]));
    
}
