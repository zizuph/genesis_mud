#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(57);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f20",
        "southwest" : "r01/f18",
        "south" : "r01/f19",
        "northwest" : "r03/f18",
        "east" : "r02/f20",
        "north" : "r03/f19",
        "northeast" : "r03/f20",
        "west" : "r02/f18",
    ]));
    
}
