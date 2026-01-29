#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f20",
        "southwest" : "r05/f18",
        "south" : "r05/f19",
        "northwest" : "r03/f18",
        "east" : "r04/f20",
        "north" : "r03/f19",
        "northeast" : "r03/f20",
        "west" : "r04/f18",
    ]));
    
}
