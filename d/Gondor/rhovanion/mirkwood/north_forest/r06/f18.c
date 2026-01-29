#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(78);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r05/f19",
        "southwest" : "r05/f17",
        "south" : "r05/f18",
        "northwest" : "r07/f17",
        "east" : "r06/f19",
        "north" : "r07/f18",
        "northeast" : "r07/f19",
        "west" : "r06/f17",
    ]));
    
}
