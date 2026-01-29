#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r03/f08",
        "southwest" : "r03/f06",
        "south" : "r03/f07",
        "northwest" : "r05/f06",
        "east" : "r04/f08",
        "north" : "r05/f07",
        "northeast" : "r05/f08",
        "west" : "r04/f06",
    ]));
    
}
