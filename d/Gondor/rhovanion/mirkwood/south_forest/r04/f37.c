#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(50);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f38",
        "southwest" : "r05/f36",
        "south" : "r05/f37",
        "northwest" : "r03/f36",
        "east" : "r04/f38",
        "north" : "r03/f37",
        "northeast" : "r03/f38",
        "west" : "r04/f36",
    ]));
    
}
