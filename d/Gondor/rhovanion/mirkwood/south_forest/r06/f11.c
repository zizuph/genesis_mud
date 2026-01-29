#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r07/f12",
        "southwest" : "r07/f10",
        "south" : "r07/f11",
        "northwest" : "r05/f10",
        "east" : "r06/f12",
        "north" : "r05/f11",
        "northeast" : "r05/f12",
        "west" : "r06/f10",
    ]));
    
}
