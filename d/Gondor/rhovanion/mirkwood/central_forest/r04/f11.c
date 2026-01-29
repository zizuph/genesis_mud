#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r03/f12",
        "southwest" : "r03/f10",
        "south" : "r03/f11",
        "northwest" : "r05/f10",
        "east" : "r04/f12",
        "north" : "r05/f11",
        "northeast" : "r05/f12",
        "west" : "r04/f10",
    ]));
    
}
