#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(28);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r05/f13",
        "southwest" : "r05/f11",
        "south" : "r05/f12",
        "northwest" : "r07/f11",
        "east" : "r06/f13",
        "north" : "r07/f12",
        "northeast" : "r07/f13",
        "west" : "r06/f11",
    ]));
    
}
