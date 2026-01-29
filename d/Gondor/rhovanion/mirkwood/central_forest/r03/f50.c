#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f51",
        "southwest" : "r02/f49",
        "south" : "r02/f50",
        "northwest" : "r04/f49",
        "east" : "r03/f51",
        "north" : "r04/f50",
        "northeast" : "r04/f51",
        "west" : "r03/f49",
    ]));
    
}
