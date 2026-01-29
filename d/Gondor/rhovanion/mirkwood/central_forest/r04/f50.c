#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r03/f51",
        "southwest" : "r03/f49",
        "south" : "r03/f50",
        "northwest" : "r05/f49",
        "east" : "r04/f51",
        "north" : "r05/f50",
        "northeast" : "r05/f51",
        "west" : "r04/f49",
    ]));
    
}
