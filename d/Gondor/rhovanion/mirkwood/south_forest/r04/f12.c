#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r05/f13",
        "southwest" : "r05/f11",
        "south" : "r05/f12",
        "northwest" : "r03/f11",
        "east" : "r04/f13",
        "north" : "r03/f12",
        "northeast" : "r03/f13",
        "west" : "r04/f11",
    ]));
    
}
