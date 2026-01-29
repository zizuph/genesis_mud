#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f24",
        "southwest" : "r04/f22",
        "south" : "r04/f23",
        "northwest" : "r02/f22",
        "east" : "r03/f24",
        "north" : "r02/f23",
        "northeast" : "r02/f24",
        "west" : "r03/f22",
    ]));
    
}
