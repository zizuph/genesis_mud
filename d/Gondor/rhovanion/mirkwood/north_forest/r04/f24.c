#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(47);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r03/f25",
        "southwest" : "r03/f23",
        "south" : "r03/f24",
        "northwest" : "r05/f23",
        "east" : "r04/f25",
        "north" : "r05/f24",
        "northeast" : "r05/f25",
        "west" : "r04/f23",
    ]));
    
}
