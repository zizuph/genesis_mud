#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(75);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r04/f18",
        "southwest" : "r04/f16",
        "south" : "r04/f17",
        "northwest" : "r06/f16",
        "east" : "r05/f18",
        "north" : "r06/f17",
        "northeast" : "r06/f18",
        "west" : "r05/f16",
    ]));
    
}
