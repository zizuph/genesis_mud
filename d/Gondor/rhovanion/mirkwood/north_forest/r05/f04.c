#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f05",
        "southwest" : "r04/f03",
        "south" : "r04/f04",
        "northwest" : "r06/f03",
        "east" : "r05/f05",
        "north" : "r06/f04",
        "northeast" : "r06/f05",
        "west" : "r05/f03",
    ]));
    
}
