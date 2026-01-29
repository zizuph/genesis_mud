#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(36);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r03/f13",
        "southwest" : "r03/f11",
        "south" : "r03/f12",
        "northwest" : "r05/f11",
        "east" : "r04/f13",
        "north" : "r05/f12",
        "northeast" : "r05/f13",
        "west" : "r04/f11",
    ]));
    
}
