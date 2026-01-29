#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r02/f05",
        "southwest" : "r02/f03",
        "south" : "r02/f04",
        "northwest" : "r04/f03",
        "east" : "r03/f05",
        "north" : "r04/f04",
        "northeast" : "r04/f05",
        "west" : "r03/f03",
    ]));
    
}
