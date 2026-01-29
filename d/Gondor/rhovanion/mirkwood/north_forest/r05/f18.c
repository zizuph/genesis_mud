#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(89);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r04/f19",
        "southwest" : "r04/f17",
        "south" : "r04/f18",
        "northwest" : "r06/f17",
        "east" : "r05/f19",
        "north" : "r06/f18",
        "northeast" : "r06/f19",
        "west" : "r05/f17",
    ]));
    
}
