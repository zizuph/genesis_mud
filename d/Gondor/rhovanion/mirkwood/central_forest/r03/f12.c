#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f13",
        "southwest" : "r02/f11",
        "south" : "r02/f12",
        "northwest" : "r04/f11",
        "east" : "r03/f13",
        "north" : "r04/f12",
        "northeast" : "r04/f13",
        "west" : "r03/f11",
    ]));
    
}
