#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f18",
        "southwest" : "r05/f16",
        "south" : "r05/f17",
        "northwest" : "r03/f16",
        "east" : "r04/f18",
        "north" : "r03/f17",
        "northeast" : "r03/f18",
        "west" : "r04/f16",
    ]));
    
}
