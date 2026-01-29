#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f23",
        "southwest" : "r05/f21",
        "south" : "r05/f22",
        "northwest" : "r03/f21",
        "east" : "r04/f23",
        "north" : "r03/f22",
        "northeast" : "r03/f23",
        "west" : "r04/f21",
    ]));
    
}
