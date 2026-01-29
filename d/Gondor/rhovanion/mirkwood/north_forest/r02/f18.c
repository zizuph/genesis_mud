#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(38);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f19",
        "southwest" : "r01/f17",
        "south" : "r01/f18",
        "northwest" : "r03/f17",
        "east" : "r02/f19",
        "north" : "r03/f18",
        "northeast" : "r03/f19",
        "west" : "r02/f17",
    ]));
    
}
