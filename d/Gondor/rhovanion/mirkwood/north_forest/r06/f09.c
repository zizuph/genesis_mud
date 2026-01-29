#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(21);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r05/f10",
        "southwest" : "r05/f08",
        "south" : "r05/f09",
        "northwest" : "r07/f08",
        "east" : "r06/f10",
        "north" : "r07/f09",
        "northeast" : "r07/f10",
        "west" : "r06/f08",
    ]));
    
}
