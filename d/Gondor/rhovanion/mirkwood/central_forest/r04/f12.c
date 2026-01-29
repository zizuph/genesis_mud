#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f13",
        "southwest" : "r03/f11",
        "south" : "r03/f12",
        "northwest" : "r05/f11",
        "east" : "r04/f13",
        "north" : "r05/f12",
        "northeast" : "r05/f13",
        "west" : "r04/f11",
    ]));
    
}
