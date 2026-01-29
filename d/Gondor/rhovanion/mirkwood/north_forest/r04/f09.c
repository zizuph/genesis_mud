#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(28);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r03/f10",
        "southwest" : "r03/f08",
        "south" : "r03/f09",
        "northwest" : "r05/f08",
        "east" : "r04/f10",
        "north" : "r05/f09",
        "northeast" : "r05/f10",
        "west" : "r04/f08",
    ]));
    
}
