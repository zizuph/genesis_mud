#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(62);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r05/f21",
        "southwest" : "r05/f19",
        "south" : "r05/f20",
        "northwest" : "r07/f19",
        "east" : "r06/f21",
        "north" : "r07/f20",
        "northeast" : "r07/f21",
        "west" : "r06/f19",
    ]));
    
}
