#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(82);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f26",
        "southwest" : "r03/f24",
        "south" : "r03/f25",
        "northwest" : "r05/m24",
        "east" : "r04/f26",
        "north" : "r05/m25",
        "northeast" : "r05/m26",
        "west" : "r04/f24",
    ]));
    
}
