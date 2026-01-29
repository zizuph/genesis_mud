#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(66);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r04/f22",
        "southwest" : "r04/f20",
        "south" : "r04/f21",
        "northwest" : "r06/f20",
        "east" : "r05/f22",
        "north" : "r06/f21",
        "northeast" : "r06/f22",
        "west" : "r05/f20",
    ]));
    
}
