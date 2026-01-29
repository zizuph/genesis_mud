#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(20);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r05/f09",
        "southwest" : "r05/f07",
        "south" : "r05/f08",
        "northwest" : "r07/f07",
        "east" : "r06/f09",
        "north" : "r07/f08",
        "northeast" : "r07/f09",
        "west" : "r06/f07",
    ]));
    
}
