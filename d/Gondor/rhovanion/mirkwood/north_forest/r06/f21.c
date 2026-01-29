#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(58);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r05/f22",
        "southwest" : "r05/f20",
        "south" : "r05/f21",
        "northwest" : "r07/f20",
        "east" : "r06/f22",
        "north" : "r07/f21",
        "northeast" : "r07/f22",
        "west" : "r06/f20",
    ]));
    
}
