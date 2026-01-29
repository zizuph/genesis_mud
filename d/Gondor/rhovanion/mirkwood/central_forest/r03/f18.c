#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f19",
        "southwest" : "r02/f17",
        "south" : "r02/f18",
        "northwest" : "r04/f17",
        "east" : "r03/f19",
        "north" : "r04/f18",
        "northeast" : "r04/f19",
        "west" : "r03/f17",
    ]));
    
}
