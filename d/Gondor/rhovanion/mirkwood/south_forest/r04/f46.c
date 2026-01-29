#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f47",
        "southwest" : "r05/f45",
        "south" : "r05/f46",
        "northwest" : "r03/f45",
        "east" : "r04/f47",
        "north" : "r03/f46",
        "northeast" : "r03/f47",
        "west" : "r04/f45",
    ]));
    
}
