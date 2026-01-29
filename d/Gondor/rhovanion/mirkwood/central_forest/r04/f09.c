#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r03/f10",
        "southwest" : "r03/f08",
        "south" : "r03/f09",
        "northwest" : "r05/f08",
        "east" : "r04/f10",
        "north" : "r05/f09",
        "northeast" : "r05/f10",
        "west" : "r04/f08",
    ]));
    
}
