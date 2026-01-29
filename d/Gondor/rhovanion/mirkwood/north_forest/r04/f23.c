#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(46);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r03/f24",
        "southwest" : "r03/f22",
        "south" : "r03/f23",
        "northwest" : "r05/f22",
        "east" : "r04/f24",
        "north" : "r05/f23",
        "northeast" : "r05/f24",
        "west" : "r04/f22",
    ]));
    
}
