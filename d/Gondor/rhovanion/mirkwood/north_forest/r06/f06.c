#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(36);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r05/f07",
        "southwest" : "r05/f05",
        "south" : "r05/f06",
        "northwest" : "r07/f05",
        "east" : "r06/f07",
        "north" : "r07/f06",
        "northeast" : "r07/f07",
        "west" : "r06/f05",
    ]));
    
}
