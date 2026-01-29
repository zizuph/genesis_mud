#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(38);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r05/f11",
        "southwest" : "r05/f09",
        "south" : "r05/f10",
        "northwest" : "r07/f09",
        "east" : "r06/f11",
        "north" : "r07/f10",
        "northeast" : "r07/f11",
        "west" : "r06/f09",
    ]));
    
}
