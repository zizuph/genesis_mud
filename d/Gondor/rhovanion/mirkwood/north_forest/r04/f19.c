#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(69);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r03/f20",
        "southwest" : "r03/f18",
        "south" : "r03/f19",
        "northwest" : "r05/f18",
        "east" : "r04/f20",
        "north" : "r05/f19",
        "northeast" : "r05/f20",
        "west" : "r04/f18",
    ]));
    
}
