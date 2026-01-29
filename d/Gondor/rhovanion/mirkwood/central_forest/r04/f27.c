#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(88);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f28",
        "southwest" : "r03/f26",
        "south" : "r03/f27",
        "northwest" : "r05/m26",
        "east" : "r04/f28",
        "north" : "r05/m27",
        "northeast" : "r05/m28",
        "west" : "r04/f26",
    ]));
    
}
