#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f20",
        "southwest" : "r02/f18",
        "south" : "r02/f19",
        "northwest" : "r04/f18",
        "east" : "r03/f20",
        "north" : "r04/f19",
        "northeast" : "r04/f20",
        "west" : "r03/f18",
    ]));
    
}
