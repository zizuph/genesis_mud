#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(52);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r03/f18",
        "southwest" : "r03/f16",
        "south" : "r03/f17",
        "northwest" : "r05/f16",
        "east" : "r04/f18",
        "north" : "r05/f17",
        "northeast" : "r05/f18",
        "west" : "r04/f16",
    ]));
    
}
