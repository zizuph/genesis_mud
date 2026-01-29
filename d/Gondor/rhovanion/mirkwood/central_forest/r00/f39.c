#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r33",
        "south" : MIRKWOOD_OLDROAD_DIR + "r34",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r35",
        
        "northwest" : "r01/f38",
        "east" : "r00/f40",
        "north" : "r01/f39",
        "northeast" : "r01/f40",
        "west" : "r00/f38",
    ]));
    
}
