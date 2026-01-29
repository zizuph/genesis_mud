#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r04/f04",
        "southwest" : "r04/f02",
        "south" : "r04/f03",
        "northwest" : "r06/f02",
        "east" : "r05/f04",
        "north" : "r06/f03",
        "northeast" : "r06/f04",
        "west" : "r05/f02",
    ]));
    
}
