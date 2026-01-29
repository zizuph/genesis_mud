#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(62);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f19",
        "southwest" : "r03/f17",
        "south" : "r03/f18",
        "northwest" : "r05/f17",
        "east" : "r04/f19",
        "north" : "r05/f18",
        "northeast" : "r05/f19",
        "west" : "r04/f17",
    ]));
    
}
