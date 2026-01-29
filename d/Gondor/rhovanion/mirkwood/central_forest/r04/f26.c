#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(81);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f27",
        "southwest" : "r03/f25",
        "south" : "r03/f26",
        "northwest" : "r05/m25",
        "east" : "r04/f27",
        "north" : "r05/m26",
        "northeast" : "r05/m27",
        "west" : "r04/f25",
    ]));
    
}
