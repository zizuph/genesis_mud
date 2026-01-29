#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(28);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f06",
        "southwest" : "r05/f04",
        "south" : "r05/f05",
        "northwest" : "r07/f04",
        "east" : "r06/f06",
        "north" : "r07/f05",
        "northeast" : "r07/f06",
        "west" : "r06/f04",
    ]));
    
}
