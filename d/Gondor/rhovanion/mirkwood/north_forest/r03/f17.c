#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(41);

    set_distance_to_edge(2);
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
