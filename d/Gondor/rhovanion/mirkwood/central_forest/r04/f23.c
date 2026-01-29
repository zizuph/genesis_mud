#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(83);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f24",
        "southwest" : "r03/f22",
        "south" : "r03/f23",
        "northwest" : "r05/m22",
        "east" : "r04/f24",
        "north" : "r05/m23",
        "northeast" : "r05/m24",
        "west" : "r04/f22",
    ]));
    
}
