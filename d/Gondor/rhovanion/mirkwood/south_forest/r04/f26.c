#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f27",
        "southwest" : "r05/f25",
        "south" : "r05/f26",
        "northwest" : "r03/f25",
        "east" : "r04/f27",
        "north" : "r03/f26",
        "northeast" : "r03/f27",
        "west" : "r04/f25",
    ]));
    
}
