#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r03/f05",
        "southwest" : "r03/f03",
        "south" : "r03/f04",
        "northwest" : "r05/f03",
        "east" : "r04/f05",
        "north" : "r05/f04",
        "northeast" : "r05/f05",
        "west" : "r04/f03",
    ]));
    
}
