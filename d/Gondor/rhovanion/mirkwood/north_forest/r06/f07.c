#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(22);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r05/f08",
        "southwest" : "r05/f06",
        "south" : "r05/f07",
        "northwest" : "r07/f06",
        "east" : "r06/f08",
        "north" : "r07/f07",
        "northeast" : "r07/f08",
        "west" : "r06/f06",
    ]));
    
}
