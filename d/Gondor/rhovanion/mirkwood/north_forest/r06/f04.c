#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(23);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r05/f05",
        "southwest" : "r05/f03",
        "south" : "r05/f04",
        "northwest" : "r07/f03",
        "east" : "r06/f05",
        "north" : "r07/f04",
        "northeast" : "r07/f05",
        "west" : "r06/f03",
    ]));
    
}
