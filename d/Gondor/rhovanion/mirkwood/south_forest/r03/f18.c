#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f19",
        "southwest" : "r04/f17",
        "south" : "r04/f18",
        "northwest" : "r02/f17",
        "east" : "r03/f19",
        "north" : "r02/f18",
        "northeast" : "r02/f19",
        "west" : "r03/f17",
    ]));
    
}
