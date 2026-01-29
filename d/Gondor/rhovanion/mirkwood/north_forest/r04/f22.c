#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(42);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f23",
        "southwest" : "r03/f21",
        "south" : "r03/f22",
        "northwest" : "r05/f21",
        "east" : "r04/f23",
        "north" : "r05/f22",
        "northeast" : "r05/f23",
        "west" : "r04/f21",
    ]));
    
}
