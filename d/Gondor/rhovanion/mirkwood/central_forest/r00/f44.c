#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_OLDROAD_DIR + "r38",
        "south" : MIRKWOOD_OLDROAD_DIR + "r39",
        "southeast" : MIRKWOOD_OLDROAD_DIR + "r40",
        
        "northwest" : "r01/f43",
        "east" : "r00/f45",
        "north" : "r01/f44",
        "northeast" : "r01/f45",
        "west" : "r00/f43",
    ]));
    
}
