#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(65);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f21",
        "southwest" : "r03/f19",
        "south" : "r03/f20",
        "northwest" : "r05/f19",
        "east" : "r04/f21",
        "north" : "r05/f20",
        "northeast" : "r05/f21",
        "west" : "r04/f19",
    ]));
    
}
