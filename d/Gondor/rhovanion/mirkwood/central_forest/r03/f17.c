#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f18",
        "southwest" : "r02/f16",
        "south" : "r02/f17",
        "northwest" : "r04/f16",
        "east" : "r03/f18",
        "north" : "r04/f17",
        "northeast" : "r04/f18",
        "west" : "r03/f16",
    ]));
    
}
