#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(24);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r04/f13",
        "southwest" : "r04/f11",
        "south" : "r04/f12",
        "northwest" : "r06/f11",
        "east" : "r05/f13",
        "north" : "r06/f12",
        "northeast" : "r06/f13",
        "west" : "r05/f11",
    ]));
    
}
