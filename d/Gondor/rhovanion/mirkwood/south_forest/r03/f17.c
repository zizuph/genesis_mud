#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f18",
        "southwest" : "r04/f16",
        "south" : "r04/f17",
        "northwest" : "r02/f16",
        "east" : "r03/f18",
        "north" : "r02/f17",
        "northeast" : "r02/f18",
        "west" : "r03/f16",
    ]));
    
}
